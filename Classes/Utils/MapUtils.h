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
    Direction vecToMapDirection(const Vec2& vec);
    vector<Direction> vecToDirections(const Vec2& vec);
    Vec2 getUnitVector(const Direction& direction);
    bool intersectsGridRect(const Rect& rect1, const Rect& rect2);
}

#endif // __MAP_UTILS_H__