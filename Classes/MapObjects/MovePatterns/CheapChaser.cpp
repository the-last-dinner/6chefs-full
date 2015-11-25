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
void CheapChaser::start(const Rect& gridRect)
{
    MovePattern::start(gridRect);
    
    this->move();
}

// パーティが移動した時
void CheapChaser::onPartyMoved(const Rect& gridRect)
{
    MovePattern::onPartyMoved(gridRect);
    
    // もしキャラクタが動いていなければ、動かす
    if(this->chara->isMoving()) return;
    this->move();
}

// マップ移動可能か
bool CheapChaser::canGoToNextMap() const
{
    return !this->chara->isHit(MapUtils::vectoMapDirections(this->mainCharacterRect.origin - this->chara->getGridPosition() - Vec2(-1, -1)));
}

// 移動
void CheapChaser::move()
{
    this->chara->walkBy(MapUtils::vectoMapDirections(this->mainCharacterRect.origin - this->chara->getGridPosition() - Vec2(-1, -1)), CC_CALLBACK_0(CheapChaser::move, this));
}
