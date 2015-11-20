//
//  CheapChaser.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/CheapChaser.h"

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