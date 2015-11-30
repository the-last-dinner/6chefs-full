//
//  Scouter.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/Scouter.h"

// コンストラクタ
Scouter::Scouter() {FUNCLOG};

// デストラクタ
Scouter::~Scouter() {FUNCLOG};

// 初期化
bool Scouter::init(Character* character)
{
    if(!MovePattern::init(character)) return false;
    
    return true;
}