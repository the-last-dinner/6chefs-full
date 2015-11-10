//
//  MapUtils.h
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#ifndef __MAP_UTILS_H__
#define __MAP_UTILS_H__

#include "define.h"

namespace MapUtils
{
	Point convertToMapPoint(const Size& mapSize, const Point& ccPoint);
	Point convertToCCPoint(const Size& mapSize, const Point& gridPoint);
    Point convertToDispPosition(const Point& mapPosition, const Point& objectPosition);
    Point getGridVector(const Direction& direction);
    float   getGridNum(float length);
    Direction keyToDirection(const Key& key);
    vector<Direction> keyToDirection(const vector<Key>& keys);
    Direction toEnumDirection(const string& sDirection);
    vector<Direction> vecToDirection(const Vec2& vec);
    Vec2 getUnitVector(const Direction& direction);
}

#endif // __MAP_UTILS_H__