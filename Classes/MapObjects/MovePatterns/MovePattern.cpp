//
//  MovePattern.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#include "MapObjects/MovePatterns/MovePattern.h"

// コンストラクタ
MovePattern::MovePattern() {};

// デストラクタ
MovePattern::~MovePattern() {};

// 初期化
bool MovePattern::init(Character* chara)
{
    if(!chara) return false;
    
    this->chara = chara;
    
    return true;
}