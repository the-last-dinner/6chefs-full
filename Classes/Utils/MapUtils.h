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
	Point convertToMapPoint(const Size& mapSize, Point ccPoint);
	Point convertToCCPoint(const Size& mapSize, Point gridPoint);
    Point getGridVector(const Direction& direction);
    Direction keyToDirection(const Key& key);
}

#endif // __MAP_UTILS_H__
