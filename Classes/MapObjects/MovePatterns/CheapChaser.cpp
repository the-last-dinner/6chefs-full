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
    return this->chara->canMove(MapUtils::vectoMapDirections(this->mainCharacterRect.origin - this->chara->getGridPosition()));
}

// 次マップへの出現遅延時間を計算
float CheapChaser::calcSummonDelay() const
{
    Vec2 diffVec { this->mainCharacterRect.origin - this->chara->getGridPosition() };
    
    // 差が大きい方の要素を距離として時間を計算
    float distance { max(diffVec.x, diffVec.y) };
    
    return distance * MapObject::DURATION_MOVE_ONE_GRID * this->speedRatio;
}

// 移動
void CheapChaser::move()
{
    this->chara->walkBy(MapUtils::vectoMapDirections(this->mainCharacterRect.origin - this->chara->getGridPosition()), CC_CALLBACK_0(CheapChaser::move, this), this->speedRatio);
}
