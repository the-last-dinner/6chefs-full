//
//  RandomMove.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#include "MapObjects/MovePatterns/RandomMove.h"

#include "MapObjects/Character.h"

// create関数
RandomMove* RandomMove::create(Character* chara, float second)
{
    RandomMove* p {new(nothrow) RandomMove()};
    if(p && p->init(chara, second))
    {
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = nullptr;
        return nullptr;
    }
}

// コンストラクタ
RandomMove::RandomMove() {FUNCLOG};

// デストラクタ
RandomMove::~RandomMove() {FUNCLOG};

// 初期化
bool RandomMove::init(Character* chara, float second)
{
    if(!MovePattern::init(chara)) return false;
    
    this->second = second;
    
    return true;
}

// 動かす
void RandomMove::move()
{
    // 移動可能な方向のベクタを用意
    vector<Direction> enableDirections {};
    for(int i {0}; i < static_cast<int>(Direction::SIZE); i++)
    {
        Direction direction {static_cast<Direction>(i)};
        if(!this->chara->isHit(direction)) enableDirections.push_back(direction);
    }
    
    // 移動可能方向がなければ終了
    if (enableDirections.empty()) return;
    
    // 移動可能方向からランダムな要素を取り出す
    vector<Direction> detectedDirs {enableDirections[cocos2d::random(0, static_cast<int>(enableDirections.size()))]};
    
    this->chara->walkBy(detectedDirs, 1, [this]{this->move();});
}