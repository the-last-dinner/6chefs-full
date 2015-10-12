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
	this->light = light;
	this->addChild(light);
	light->setOpacity(0);
	this->runAction(TargetedAction::create(light, FadeIn::create(0.5f)));
    
    // 環境光レイヤーに光源として追加
    ambientLightLayer->addLightSource(this, light->getInformation());
}

// ライトを消す
void MapObject::removeLight()
{
	this->runAction(Sequence::createWithTwoActions(TargetedAction::create(this->light, FadeOut::create(0.5f)), TargetedAction::create(this->light, RemoveSelf::create())));
}

// リアクションアイコンを表示
ActionInterval* MapObject::createReaction()
{
    Sprite* icon {Sprite::createWithSpriteFrameName("icon_sign.png")};
    icon->setPosition(Point(0, this->getContentSize().height));
    icon->setScaleY(0.1f);
    this->addChild(icon);
    return TargetedAction::create(icon, Sequence::create(EaseElasticInOut::create(ScaleTo::create(0.6f, 1.f, 1.f)), DelayTime::create(1.f),RemoveSelf::create() ,nullptr));
}

// イベントIDを取得
int MapObject::getEventId()
{return this->eventId;}

// triggerを取得
Trigger MapObject::getTrigger()
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