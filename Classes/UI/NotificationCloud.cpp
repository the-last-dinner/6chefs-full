//
//  NotificationCloud.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#include "UI/NotificationCloud.h"

#include "UI/Cloud.h"

// 定数
const float NotificationCloud::MARGIN_H {50.f};
const float NotificationCloud::MARGIN_V {70};
const float NotificationCloud::ANIMATION_DURATION {1.f};
const float NotificationCloud::DURATION {5.f};

// コンストラクタ
NotificationCloud::NotificationCloud() {FUNCLOG};

// デストラクタ
NotificationCloud::~NotificationCloud() {FUNCLOG};

// 初期化
bool NotificationCloud::init(const string& message)
{
    if(!Node::init()) return false;
    
    // カスケード
    this->setCascadeColorEnabled(true);
    this->setCascadeOpacityEnabled(true);
    
    this->setOpacity(0);
    
    // ラベルを生成
    Label* label { Label::createWithTTF(message, Resource::Font::system, 30.f) };
    
    // 背景を生成
    Cloud* bg { Cloud::create(label->getContentSize() + Size(MARGIN_H, MARGIN_V)) };
    this->addChild(bg);
    label->setPosition(bg->getContentSize() / 2);
    this->addChild(label);
    
    this->setContentSize(label->getContentSize() + Size(MARGIN_H, MARGIN_V));
    
    return true;
}

// 通知
void NotificationCloud::notify(function<void()> callback)
{
    Point toPosition {this->getPosition()};
    this->setPosition(toPosition - Vec2(0, 30.f));
    this->runAction(Spawn::createWithTwoActions(FadeIn::create(ANIMATION_DURATION), EaseCubicActionOut::create(MoveTo::create(ANIMATION_DURATION, toPosition))));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(ANIMATION_DURATION), CallFunc::create([this, callback]{this->onShowAnimationFinished(callback);})));
}

// 表示アニメーション終了時
void NotificationCloud::onShowAnimationFinished(function<void()> callback)
{
    this->runAction(Sequence::create(DelayTime::create(DURATION),
                                     Spawn::createWithTwoActions(FadeOut::create(ANIMATION_DURATION),
                                                                 EaseCubicActionIn::create(MoveBy::create(ANIMATION_DURATION, Vec2(0, -30.f)))),
                                     CallFunc::create(callback),
                                     RemoveSelf::create(),
                                     nullptr));
}