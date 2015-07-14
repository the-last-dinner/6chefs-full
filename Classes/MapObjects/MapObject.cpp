//
//  MapObject.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/21.
//
//

#include "MapObject.h"

// コンストラクタ
MapObject::MapObject():
objectSize(),
eventId(-1),
trigger(TriggerType::NONE),
_isHit(false),
movingDirection(Direction::NONE)
{FUNCLOG}

// デストラクタ
MapObject::~MapObject()
{FUNCLOG}

// マップ上のマス座標を取得(一番左下のマス座標を返す)
Point MapObject::getGridPosition(const Size& mapSize)
{
	return MapUtils::convertToMapPoint(mapSize, Point(this->getPositionX() - this->objectSize.width / 2, this->getPositionY())) / GRID;
}

// マップ上のマス座標にセット
void MapObject::setGridPosition(const Size& mapSize, const Point& mapGridPoint)
{
	Point cocosPoint = MapUtils::convertToCCPoint(mapSize, mapGridPoint);
	this->setPosition(cocosPoint.x + this->objectSize.width / 2, cocosPoint.y);
	return;
}

// マップオブジェクトの大きさをセット
void MapObject::setObjectSize(const Size& objSize)
{
	this->objectSize = objSize;
	return;
}

// イベントIDをセット
void MapObject::setEventId(int eventId)
{
	this->eventId = eventId;
	return;
}

// イベントのtriggerをセット
void MapObject::setTrigger(TriggerType trigger)
{
	this->trigger = trigger;
	return;
}

// 当たり判定の有無をセット
void MapObject::setHit(bool _isHit)
{
	this->_isHit = _isHit;
	return;
}

// 動いている方向をセット
void MapObject::setMovingDirection(Direction direction)
{
	this->movingDirection = direction;
	return;
}

// オブジェクトの大きさを取得
Size MapObject::getObjectSize()
{return this->objectSize;}

// イベントIDを取得
int MapObject::getEventId()
{return this->eventId;}

// triggerを取得
TriggerType MapObject::getTrigger()
{return this->trigger;}

// 当たり判定の有無を取得
bool MapObject::isHit()
{return this->_isHit;}

// 動いている方向を取得
Direction MapObject::getMovingDirection()
{return this->movingDirection;}