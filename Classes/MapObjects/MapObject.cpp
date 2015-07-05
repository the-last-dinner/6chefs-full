//
//  MapObject.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/21.
//
//

#include "MapObject.h"

MapObject::MapObject():
objectSize()
{FUNCLOG}

MapObject::~MapObject()
{FUNCLOG}

// マップ上のマス座標を取得(一番左下のマス座標を返す)
Point MapObject::getGridPosition(const Size& mapSize)
{
	FUNCLOG
	return MapUtils::convertToMapPoint(mapSize, Point(this->getPositionX() - this->objectSize.width / 2, this->getPositionY())) / GRID;
}

// マップ上のマス座標にセット
void MapObject::setGridPosition(const Size& mapSize, const Point& mapGridPoint)
{
	FUNCLOG
	Point cocosPoint = MapUtils::convertToCCPoint(mapSize, mapGridPoint);
	this->setPosition(cocosPoint.x + this->objectSize.width / 2, cocosPoint.y);
	return;
}

// 指定の方向に対しての当たり判定を取得
bool MapObject::isHit(const Direction direction)
{
	FUNCLOG
	
	// マップオブジェクトが縦横何マスか
	Size objSize = this->objectSize / GRID;
	
	switch (direction)
	{
		case Direction::FRONT:
			// 下方向の場合
			break;
		case Direction::RIGHT:
			// 右方向の場合
			break;
		case Direction::LEFT:
			// 左方向の場合
			break;
		case Direction::BACK:
			// 上方向の場合
			break;
		default:
			break;
	}
	return false;
}

// マップオブジェクトの大きさをセット
void MapObject::setObjectSize(const Size& objSize)
{
	FUNCLOG
	this->objectSize = objSize;
	return;
}

// イベントIDをセット
void MapObject::setEventId(int eventId)
{
	FUNCLOG
	this->eventId = eventId;
	return;
}

// イベントのtriggerをセット
void MapObject::setTrigger(TriggerType trigger)
{
	FUNCLOG
	this->trigger = trigger;
	return;
}
