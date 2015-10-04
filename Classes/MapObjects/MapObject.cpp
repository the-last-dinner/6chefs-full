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
    return TargetedAction::create(icon, EaseElasticInOut::create(ScaleTo::create(0.6f, 1.f, 1.f)));
}

// イベントIDを取得
int MapObject::getEventId()
{return this->eventId;}

// triggerを取得
Trigger MapObject::getTrigger()
{return this->trigger;}

// 当たり判定の有無を取得
bool MapObject::isHit() const
{return this->_isHit;}

// 動いている方向を取得
Direction MapObject::getMovingDirection()
{return this->movingDirection;}

// 衝突判定用Rectを取得
Rect MapObject::getCollisionRect() const
{
    return Rect(this->getPosition().x + this->collisionRect.getMinX() - this->getContentSize().width / 2, this->getPosition().y + this->collisionRect.getMinY() - getContentSize().height / 2, this->collisionRect.size.width, this->collisionRect.size.height);
}

// 隣接するマスの中心座標を取得
Point MapObject::getAdjacentPosition(const Direction& direction) const
{
    Point position { Point(this->getCollisionRect().getMidX(), this->getCollisionRect().getMidY())};
    float length {(direction == Direction::FRONT || direction == Direction::BACK)? this->getCollisionRect().size.height : this->getCollisionRect().size.width};
    position += (1 + MapUtils::getGridNum(length)) * MapUtils::getGridVector(direction) / 2;
    
    return position;
}

// 隣接するマスの中心座標を取得
Point MapObject::getAdjacentPosition(const Direction (&directions)[2]) const
{
    Point position { Point(this->getCollisionRect().getMidX(), this->getCollisionRect().getMidY())};
    int time {directions[0] == directions[1]?1:2};
    for(int i {0}; i < time; i++)
    {
        if(directions[i] == Direction::SIZE) continue;
        float length {(directions[i] == Direction::FRONT || directions[i] == Direction::BACK)? this->getCollisionRect().size.height : this->getCollisionRect().size.width};
        position += (1 + MapUtils::getGridNum(length)) * MapUtils::getGridVector(directions[i]) / 2;
    }
    
    return position;
}

// 指定の方向に対して当たり判定があるか
bool MapObject::isHit(const Direction& direction) const
{
    if(!this->objectList) return false;
        
    // 移動先の座標を取得
    Point point { this->getAdjacentPosition(direction)};
    MapObject* pObj {this->objectList->getMapObject(point)};
    if(!pObj) return false;
    return pObj->isHit();
}

// 座標から指定の方向に対して当たり判定があるか
bool MapObject::isHit(const Direction (&directions)[2]) const
{
    if(!this->objectList) return false;
    
    // 移動先の座標を取得
    Point point { this->getAdjacentPosition(directions)};
    MapObject* pObj {this->objectList->getMapObject(point)};
    if(!pObj) return false;
    return pObj->isHit();
}

// デバッグ用に枠を描画
void MapObject::drawDebugMask()
{
    Point vertices[]
    {
        Point::ZERO,
        Point(0, this->getContentSize().height),
        this->getContentSize(),
        Point(this->getContentSize().width, 0)
    };
    Color4F lineColor = Color4F::BLUE;
    DrawNode* draw {DrawNode::create()};
    draw->drawPolygon(vertices, 5, Color4F(0,0,0,0), 1, lineColor);
    draw->setPosition(this->getContentSize() / -2);
    draw->setGlobalZOrder(Priority::DEBUG_MASK);
    this->addChild(draw);
}