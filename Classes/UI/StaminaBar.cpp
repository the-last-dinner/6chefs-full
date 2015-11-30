//
//  StaminaBar.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/30.
//
//

#include "UI/StaminaBar.h"

// コンストラクタ
StaminaBar::StaminaBar() {FUNCLOG};

// デストラクタ
StaminaBar::~StaminaBar() {FUNCLOG};

// 初期化
bool StaminaBar::init(const Point& inPosition, const Point& outPosition)
{
    if(!SlideNode::init(inPosition, outPosition)) return false;
    
    // カスケード
    this->setCascadeOpacityEnabled(true);
    
    // 棒
    Sprite* bar {Sprite::create()};
    bar->setTextureRect(Rect(0, 0, WINDOW_WIDTH / 2, 20));
    bar->setColor(Color3B(0, 148, 122));
    
    // プログレスタイマー設置
    ProgressTimer* progressTimer { ProgressTimer::create(bar) };
    this->addChild(progressTimer);
    
    // 棒状
    progressTimer->setType(ProgressTimer::Type::BAR);
    
    // 右から左へ減少するようにする
    progressTimer->setReverseProgress(true);
    
    return true;
}

// ％を設定
void StaminaBar::setPercentage(const float percentage)
{
    this->progressTimer->setPercentage(percentage);
}

// 表示
void StaminaBar::slideIn(AnimationCallback cb)
{
    this->stopAllActions();
    this->runAction(Spawn::createWithTwoActions(EaseElasticOut::create(MoveTo::create(this->slideTime, this->inPosition), 0.5f), FadeIn::create(this->slideTime)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(this->slideTime), CallFunc::create([this, cb]{if(cb) cb(this);})));
}

// 非表示
void StaminaBar::slideOut(AnimationCallback cb)
{
    this->stopAllActions();
    this->runAction(Spawn::createWithTwoActions(EaseCubicActionIn::create(MoveTo::create(this->slideTime, this->outPosition)), FadeOut::create(this->slideTime)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(this->slideTime), CallFunc::create([this, cb]{if(cb) cb(this);})));
}