//
//  Stamina.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/29.
//
//

#include "Models/Stamina.h"

// 定数
const float Stamina::MAX_VALUE { 100.f };
const float Stamina::MIN_VALUE { 0.f };
const float Stamina::DEFAULT_STEP {1.0f};
const float Stamina::INCREASE_STEP_RATIO {0.5f};
const float Stamina::INCREASE_UPDATE_INTERVAL {0.05f};

// コンストラクタ
Stamina::Stamina() {FUNCLOG};

// デストラクタ
Stamina::~Stamina()
{
    FUNCLOG
    
    Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
};

// 初期化
bool Stamina::init()
{
    return true;
}

// スタミナ回復
void Stamina::increase()
{
    float percentage {this->percentage};
    
    percentage += this->step * INCREASE_STEP_RATIO;
    
    // 最大値以上になっていたら、最大値にする
    if(percentage > MAX_VALUE) percentage = MAX_VALUE;
    
    // メンバ変数にセット
    this->setPercentage(percentage);
}

// スタミナを設定
void Stamina::setPercentage(const float percentage)
{
    this->percentage = percentage;
    
    if(this->onPercentageChanged) this->onPercentageChanged(percentage);
}

// スタミナ減少
void Stamina::decrease()
{
    float percentage { this->percentage };
    
    percentage -= this->step;
    
    // 最低値以下になっていたら最低値にする
    if(percentage < MIN_VALUE) percentage = MIN_VALUE;
    
    // 減少中状態へ
    this->decreasing = true;
    
    // スケジュール
    if(Director::getInstance()->getScheduler()->isScheduled(CC_SCHEDULE_SELECTOR(Stamina::update), this))
    {
        Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(Stamina::update), this);
    }
    Director::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(Stamina::update), this, INCREASE_UPDATE_INTERVAL, false);
    
    // メンバ変数に設定
    this->setPercentage(percentage);
}

// スタミナがあるかどうか
bool Stamina::isEmpty() const
{
    return this->percentage == MIN_VALUE;
}

// update
void Stamina::update(float delta)
{
    this->decreasing = false;
    
    this->increase();
    
    if(this->percentage != MAX_VALUE) return;
    
    Director::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(Stamina::update), this);
}
