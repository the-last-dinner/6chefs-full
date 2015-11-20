//
//  MovePatternFactory.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/MovePatternFactory.h"

// コンストラクタ
MovePatternFactory::MovePatternFactory() {FUNCLOG};

// デストラクタ
MovePatternFactory::~MovePatternFactory() {FUNCLOG};

// 初期化
bool MovePatternFactory::init()
{
    return true;
}

MovePattern* MovePatternFactory::createMovePattern(const EnemyMovePattern type)
{
    return nullptr;
}

MovePattern* MovePatternFactory::createMovePattern(const CharacterMovePattern type)
{
    return nullptr;
}