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