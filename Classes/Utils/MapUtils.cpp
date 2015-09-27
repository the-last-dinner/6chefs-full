//
//  MapUtils.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#include "MapUtils.h"

Point MapUtils::convertToCCPoint(const Size& mapSize, Point gridPoint)
{
	return Point(gridPoint.x * GRID, mapSize.height - gridPoint.y * GRID);
}

Point MapUtils::convertToMapPoint(const Size& mapSize, Point ccPoint)
{
	return Point(ccPoint.x, (mapSize.height - ccPoint.y));
}

Point MapUtils::getGridVector(const Direction& direction)
{
    map<Direction, Point> directionToVec
    {
        {Direction::FRONT, Point(0, -GRID)},
        {Direction::RIGHT, Point(GRID, 0)},
        {Direction::LEFT, Point(-GRID, 0)},
        {Direction::BACK, Point(0, GRID)},
    };
    
    if(!directionToVec.count(direction)) return Point::ZERO;
    
    return directionToVec[direction];
}

// 方向キーを向きへ変換
Direction MapUtils::keyToDirection(const Key& key)
{
    return static_cast<Direction>(key);
}