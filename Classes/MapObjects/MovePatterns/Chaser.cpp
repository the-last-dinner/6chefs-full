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