//
//  Enemy.cpp
//  LastSupper
//
//  Created by Kohei on 2015/11/18.
//
//

#include "MapObjects/Enemy.h"

#include "MapObjects/MovePatterns/MovePattern.h"
#include "MapObjects/MovePatterns/MovePatternFactory.h"

// コンストラクタ
Enemy::Enemy() {FUNCLOG};

// デストラクタ
Enemy::~Enemy() {FUNCLOG};

// 初期化
bool Enemy::init(const EnemyData& data)
{
    if(!Character::init(data.chara_data)) return false;
    
    this->data = data;
    
    // 動きのアルゴリズムを生成
    MovePatternFactory* factory { MovePatternFactory::create() };
    CC_SAFE_RETAIN(factory);
    this->movePattern = factory->createMovePattern(data.move_pattern, this);
    CC_SAFE_RETAIN(this->movePattern);
    CC_SAFE_RELEASE(factory);
    
    return true;
}

// 敵IDを取得
int Enemy::getEnemyId() const
{
    return this->data.enemy_id;
}

// マップに配置された時
void Enemy::onEnterMap(const Rect& gridRect)
{
    if(this->movePattern) this->movePattern->start(gridRect);
}

// 主人公一行が移動した時
void Enemy::onPartyMoved(const Rect& gridRect)
{
    if(this->movePattern) this->movePattern->onPartyMoved(gridRect);
}

// データを取得
EnemyData Enemy::getEnemyData() const
{
    EnemyData data {this->data};
    
    // 位置情報を更新
    data.chara_data.location = this->getCharacterData().location;
    
    return data;
}

// マップ移動可能か
bool Enemy::canGoToNextMap() const
{
    if(!this->movePattern) return false;
    
    return this->movePattern->canGoToNextMap();
}

// 現在座標から、主人公までかかる時間を計算
float Enemy::calcSummonDelay() const
{
    if(!this->movePattern) return 0.0f;
    
    return this->movePattern->calcSummonDelay();
}
