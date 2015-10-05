//
//  MapUtils.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#include "MapUtils.h"

Point MapUtils::convertToCCPoint(const Size& mapSize, const Point& gridPoint)
{
	return Point(gridPoint.x * GRID, mapSize.height - gridPoint.y * GRID);
}

Point MapUtils::convertToMapPoint(const Size& mapSize, const Point& ccPoint)
{
	return Point(ccPoint.x, (mapSize.height - ccPoint.y));
}

// 画面上の座標を取得
Point MapUtils::convertToDispPosition(const Point& mapPosition, const Point& objectPosition)
{
    return mapPosition + objectPosition;
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

// 長さから、マス数を取得
float MapUtils::getGridNum(float length)
{
    return abs(length) / GRID;
}

// 方向キーを向きへ変換
Direction MapUtils::keyToDirection(const Key& key)
{
    // 変換できないキーの場合はSIZEを返す
    if(static_cast<int>(Direction::SIZE) <= static_cast<int>(key)) return Direction::SIZE;
    
    return static_cast<Direction>(key);
}

// 方向キーベクタを向きへ変換しスタックに詰めて返す
vector<Direction> MapUtils::keyToDirection(const vector<Key>& keys)
{
    vector<Direction> directions {};
    if(keys.empty()) return directions;
    for(Key key : keys)
    {
        Direction direction {MapUtils::keyToDirection(key)};
        if(direction != Direction::SIZE) directions.push_back(direction);
    }
    return directions;
}