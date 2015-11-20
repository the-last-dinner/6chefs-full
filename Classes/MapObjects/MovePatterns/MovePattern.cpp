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

// 主人公のマス座標を指定して移動開始
void MovePattern::start(const Rect& gridRect)
{
    this->mainCharacterRect = gridRect;
}

// 主人公一行が移動した時
void MovePattern::onPartyMoved(const Rect& gridRect)
{
    this->mainCharacterRect = gridRect;
}