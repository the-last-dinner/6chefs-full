//
//  PathFinder.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/07.
//
//

#ifndef __LastSupper__PathFinder__
#define __LastSupper__PathFinder__

#include "Common.h"

class MapObjectList;

class PathFinder : public Ref
{
// クラス宣言
private:
    class PathNode;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(PathFinder, const Size&)
    
// インスタンス変数
private:
    Size mapSize { Size::ZERO };
    int gridWidth { 0 };
    int gridHeight { 0 };
    
// インスタンスメソッド
private:
    PathFinder();
    ~PathFinder();
    bool init(const Size& mapSize);
    stack<pair<Direction, int>> find(const Rect& targetRect, const vector<Rect>& collisionRects, const Point& destPosition);
    vector<Rect> splitRectByGrid(const Rect& rect);
    
// クラス
private:
    class PathNode : public Ref
    {
    public:
        enum struct State
        {
            OPEN,
            CLOSE,
            NONE,
        };
        
        Point gridPoint {Point::ZERO};
        State state {State::NONE};
        int actualCost { 0 };
        int estimatedCost { 0 };
        PathNode* parent { nullptr };
        
        int score() { return actualCost + estimatedCost; };
    
    public:
        CREATE_FUNC_WITH_PARAM(PathNode, const Point&)
        
    private:
        bool init(const Point& gridPoint) { this->gridPoint = gridPoint; return true; };
    };
};

#endif /* defined(__LastSupper__PathFinder__) */
