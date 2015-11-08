//
//  PathFinder.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/07.
//
//

#include "PathFinder.h"

// コンストラクタ
PathFinder::PathFinder() { FUNCLOG };

// デストラクタ
PathFinder::~PathFinder() { FUNCLOG };

// 初期化
bool PathFinder::init(const Size& mapSize)
{
    this->mapSize = mapSize;
    
    // マップのマス数
    this->gridWidth = static_cast<int>(MapUtils::getGridNum(mapSize.width));
    this->gridHeight = static_cast<int>(MapUtils::getGridNum(mapSize.height));
    
    return true;
}

// A-starのアルゴリズムで経路を探索
stack<pair<Direction, int>> PathFinder::find(const Rect& targetRect, const vector<Rect>& collisionRects, const Point& destPosition)
{
    map<Point, PathNode*> nodeMap {};
    vector<PathNode*> openedNodes {};
    
    // 追跡者の幅を考慮して進入不可座標をセットする
    int targetWidth { static_cast<int>(MapUtils::getGridNum(targetRect.size.width)) };
    for(Rect collisionRect : collisionRects)
    {
        // グリッドに分割
        for(Rect rect : this->splitRectByGrid(collisionRect))
        {
            PathNode* node { PathNode::create(MapUtils::convertToMapPoint(this->mapSize, Point(rect.getMinX(), rect.getMinY())) / GRID) };
            CC_SAFE_RETAIN(node);
            node->state = PathNode::State::CLOSE;
        }
    }
    
    stack<pair<Direction, int>> temp;
    
    return temp;
}

// Rectをマスで分割
vector<Rect> PathFinder::splitRectByGrid(const Rect& rect)
{
    vector<Rect> rects {};
    int gridWidth {static_cast<int>(MapUtils::getGridNum(rect.size.width))};
    int gridHeight {static_cast<int>(MapUtils::getGridNum(rect.size.height))};
    for(int ih { 0 }; ih < gridHeight; ih++)
    {
        int originY { static_cast<int>(rect.origin.y) + ih * GRID };
        for(int iw { 0 }; iw < gridWidth; iw++)
        {
            int originX { static_cast<int>(rect.origin.x) + iw * GRID };
            rects.push_back(Rect(originX, originY, GRID, GRID));
        }
    }
    
    return rects;
}
