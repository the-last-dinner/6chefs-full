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
Point MapObject::getGridPosition()
{
	FUNCLOG
	TiledMapManager* manager = TiledMapManager::getInstance();
	return manager->toGridPoint(manager->toMapPoint(Point(this->getPositionX() - this->objectSize.width / 2, this->getPositionY())));
}

// マップ上のマス座標にセット
void MapObject::setGridPosition(const Point& mapGridPoint)
{
	FUNCLOG
	TiledMapManager* manager = TiledMapManager::getInstance();
	Point cocosPoint = manager->toCocosPoint(mapGridPoint);
	this->setPosition(cocosPoint.x + this->objectSize.width / 2, cocosPoint.y);
	return;
}

// 指定の方向に対しての当たり判定を取得
bool MapObject::isHit(const Direction direction)
{
	FUNCLOG
	// マップオブジェクトの一番左上の座標
	Point objPoint = this->getGridPosition();
	
	// マップオブジェクトが縦横何マスか
	Size objSize = this->objectSize / GRID;
	
	// マネージャー取得
	TiledMapManager* manager = TiledMapManager::getInstance();
	
	switch (direction)
	{
		case Direction::FRONT:
			// 下方向の場合
			for(int i = 0; i < objSize.width; i++)
			{
				if(manager->isHit(Point(objPoint.x + i, objPoint.y + 1))) return true;
			}
			break;
		case Direction::RIGHT:
			// 右方向の場合
			return manager->isHit(Point(objPoint.x + objSize.width, objPoint.y));
			break;
		case Direction::LEFT:
			// 左方向の場合
			return manager->isHit(Point(objPoint.x - 1, objPoint.y));
			break;
		case Direction::BACK:
			// 上方向の場合
			for(int i = 0; i < objSize.width; i++)
			{
				if(manager->isHit(Point(objPoint.x + i, objPoint.y - objSize.height + 1))) return true;
			}
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