//
//  MapObject.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/21.
//
//

#include "MapObjects/MapObject.h"

#include "MapObjects/MapObjectList.h"

#include "Effects/AmbientLightLayer.h"
#include "Effects/Light.h"

// １マス動くのにかける時間の基準値
const float MapObject::DURATION_MOVE_ONE_GRID = 0.1f;

// コンストラクタ
MapObject::MapObject(){FUNCLOG}

// デストラクタ
MapObject::~MapObject(){FUNCLOG}

// マス数サイズを取得
Size MapObject::getGridSize() const
{
    return Size(floor(this->getContentSize().width / GRID),floor(this->getContentSize().height / GRID));
}

// マップ上のマス座標を取得(一番左下のマス座標を返す)
Point MapObject::getGridPosition(const Size& mapSize) const
{
	return MapUtils::convertToMapPoint(mapSize, Point(this->getPositionX() - this->getContentSize().width / 2, this->getPositionY())) / GRID;
}

// マップ上のマス座標にセット
void MapObject::setGridPosition(const Size& mapSize, const Point& mapGridPoint)
{
	Point cocosPoint = MapUtils::convertToCCPoint(mapSize, mapGridPoint);
	this->setPosition(cocosPoint.x + this->getContentSize().width / 2, cocosPoint.y);
}

// オブジェクトIDをセット
void MapObject::setObjectId(int objectId)
{
    this->objectId = objectId;
}

// イベントIDをセット
void MapObject::setEventId(int eventId)
{
	this->eventId = eventId;
}

// イベントのtriggerをセット
void MapObject::setTrigger(Trigger trigger)
{
	this->trigger = trigger;
}

// 当たり判定の有無をセット
void MapObject::setHit(bool _isHit)
{
	this->_isHit = _isHit;
}

// 動いている方向をセット
void MapObject::setMovingDirection(Direction direction)
{
	this->movingDirection = direction;
}

// 衝突判定用Rectをセット
void MapObject::setCollisionRect(const Rect& rect)
{
    this->collisionRect = rect;
}

// マップオブジェクトのリストをセット
void MapObject::setMapObjectList(MapObjectList* objectList)
{
    this->objectList = objectList;
}

// ライトをセット
void MapObject::setLight(Light* light, AmbientLightLayer* ambientLightLayer)
{
    if(this->light)
    {
        this->light = light;
        this->addChild(light);
        light->setOpacity(0);
        this->runAction(TargetedAction::create(light, FadeIn::create(0.5f)));
    }
    
    // 環境光レイヤーに光源として追加
    ambientLightLayer->addLightSource(this, light->getInformation());
}

// ライトを消す
void MapObject::removeLight()
{
	this->runAction(Sequence::createWithTwoActions(TargetedAction::create(this->light, FadeOut::create(0.5f)), TargetedAction::create(this->light, RemoveSelf::create())));
}

// オブジェクトIDを取得
int MapObject::getObjectId() const
{return this->objectId;}

// イベントIDを取得
int MapObject::getEventId() const
{return this->eventId;}

// triggerを取得
Trigger MapObject::getTrigger() const
{return this->trigger;}

// 当たり判定の有無を取得
const bool MapObject::isHit() const
{return this->_isHit;}

// 動いている方向を取得
Direction MapObject::getMovingDirection()
{return this->movingDirection;}

// 衝突判定用Rectを取得
Rect MapObject::getCollisionRect() const
{
    return Rect(this->getPosition().x + this->collisionRect.getMinX() - this->getContentSize().width / 2, this->getPosition().y + this->collisionRect.getMinY() - getContentSize().height / 2, this->collisionRect.size.width, this->collisionRect.size.height);
}

// 指定方向に移動した場合の衝突判定用Rectを取得
Rect MapObject::getCollisionRect(const Direction& direction) const
{
    Rect rect {this->getCollisionRect()};
    
    Point movementVec {MapUtils::getGridVector(direction)};
    
    // あたり判定用Rectを縦横-2ピクセルした後に、x,y方向に1ピクセル足すことによって、関係ない範囲を巻き込まないようにしている（線分上、頂点上であっても判定がきいてしまうため）
    return Rect(rect.origin.x + 1 + movementVec.x, rect.origin.y + 1 + movementVec.y, rect.size.width - 2, rect.size.height - 2);
}

// 指定2方向に移動した場合の衝突判定用Rectを取得
Rect MapObject::getCollisionRect(const Direction (&directions)[2]) const
{
    Rect rect {this->getCollisionRect()};
    
    Point movementVec {Point::ZERO};
    
    // 二方向分の移動ベクトルを生成する
    for(int i{0};i < 2;i++)
    {
        movementVec += MapUtils::getGridVector(directions[i]);
    }
    
    // あたり判定用Rectを縦横-2ピクセルした後に、x,y方向に1ピクセル足すことによって、関係ない範囲を巻き込まないようにしている（線分上、頂点上であっても判定がきいてしまうため）
    return Rect(rect.origin.x + 1 + movementVec.x, rect.origin.y + 1 + movementVec.y, rect.size.width - 2, rect.size.height - 2);
}

// 指定の方向に対して当たり判定があるか
const bool MapObject::isHit(const Direction& direction) const
{
    if(!this->objectList) return false;
    
    return this->objectList->containsCollisionObject(this->getCollisionRect(direction));
}

// 指定の２方向に対して当たり判定があるか
const bool MapObject::isHit(const Direction (&directions)[2]) const
{
    if(!this->objectList) return false;
    
    return this->objectList->containsCollisionObject(this->getCollisionRect(directions));
}

// 方向、マス数指定移動用メソッド(移動させる時は必ずこのメソッドで)
void MapObject::moveBy(const vector<Direction>& directions, const int gridNum, function<void()> onMoved, const float ratio)
{
    if(directions.empty()) return;
    
    Vec2 movement {};
    
    // 移動ベクトルを算出
    for(Direction direction : directions)
    {
        if(direction != Direction::SIZE) movement += MapUtils::getGridVector(direction);
    }
    
    // 移動先座標をコールバック関数に送信(TiledMapLayerの関数を呼び出す)
    if(this->onMove) this->onMove(this, this->getPosition() + movement * gridNum);
    
    // 移動開始
    this->runAction(Sequence::createWithTwoActions(MoveBy::create((DURATION_MOVE_ONE_GRID * gridNum) / ratio, movement * gridNum), CallFunc::create(onMoved)));
}

// 目的地指定移動用メソッド
void MapObject::moveTo(const Point& destPosition, function<void()> onMoved, const float ratio)
{
    Vec2 movement { destPosition - this->getPosition() };
    Vector<FiniteTimeAction*> movingActions {};
    int gridNum { static_cast<int>(MapUtils::getGridNum(movement.length()))};
    
    vector<Vec2> movements {};
    
    for(int i {0}; i < gridNum; i++)
    {
        
    }
    
}

// デバッグ用に枠を描画
void MapObject::drawDebugMask()
{
    Point vertices[]
    {
        Point::ZERO,
        Point(0, this->getContentSize().height),
        this->getContentSize(),
        Point(this->getContentSize().width, 0),
	Point::ZERO,
    };
    Color4F lineColor = Color4F::BLUE;
    DrawNode* draw {DrawNode::create()};
    draw->drawPolygon(vertices, 5, Color4F(0,0,0,0), 1, lineColor);
    draw->setPosition(this->getContentSize() / -2);
    draw->setGlobalZOrder(Priority::DEBUG_MASK);
    this->addChild(draw);
}