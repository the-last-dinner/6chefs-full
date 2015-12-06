//
//  Chaser.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/Chaser.h"

// コンストラクタ
Chaser::Chaser() {FUNCLOG};

// デストラクタ
Chaser::~Chaser() {FUNCLOG};

// 初期化
bool Chaser::init(Character* character)
{
    if(!MovePattern::init(character)) return false;
    
    return true;
}

// 追跡開始
void Chaser::start(const Rect& gridRect)
{
    MovePattern::start(gridRect);
    
    
}

// マップ移動可能か
bool Chaser::canGoToNextMap() const { return true; };

// 出口までに掛る時間を計算
float Chaser::calcSummonDelay() const
{
    return 0;
}