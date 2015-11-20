//
//  CheapChaser.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/CheapChaser.h"

#include "MapObjects/Character.h"

// コンストラクタ
CheapChaser::CheapChaser() {FUNCLOG};

// デストラクタ
CheapChaser::~CheapChaser() {FUNCLOG};

// 初期化
bool CheapChaser::init(Character* character)
{
    if(!MovePattern::init(character)) return false;
    
    return true;
}

// 追跡開始
void CheapChaser::start(const Point& gridPosition)
{
    MovePattern::start(gridPosition);
    
    this->move();
}

// 移動
void CheapChaser::move()
{
    this->chara->walkBy(this->calcMoveDirection(), CC_CALLBACK_0(CheapChaser::move, this));
}

// 主人公のマス座標から方向を算出
Direction CheapChaser::calcMoveDirection()
{
    // 主人公へのベクトル
    Vec2 diffVec { this->mainCharacterPos - this->chara->getGridPosition() };
    
    // 差が大き方の要素のみを使う
    if(abs(diffVec.x) > abs(diffVec.y))
    {
        diffVec = Vec2(diffVec.x, 0);
    }
    else
    {
        diffVec = Vec2(0, diffVec.y);
    }
    
    return MapUtils::vecToMapDirection(diffVec);
}
