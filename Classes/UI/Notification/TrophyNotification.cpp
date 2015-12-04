//
//  TrophyNotification.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/05.
//
//

#include "UI/Notification/TrophyNotification.h"

#include "UI/Cloud.h"

// コンストラクタ
TrophyNotification::TrophyNotification() {FUNCLOG};

// デストラクタ
TrophyNotification::~TrophyNotification() {FUNCLOG};

// 初期化
bool TrophyNotification::init(const string& message)
{
    if(!NotificationNode::init()) return false;
    
    this->setOpacity(0);
    
    // ラベルを生成
    Label* label { Label::createWithTTF(message, Resource::Font::system, 30.f) };
    
    // トロフィ生成
    Sprite* trophy { Sprite::createWithSpriteFrameName("trophy_gold.png") };
    float trophyScale {label->getContentSize().height / trophy->getContentSize().height};
    trophy->setScale(trophyScale);
    
    // 背景を生成
    Cloud* bg { Cloud::create(Size(trophy->getContentSize().width + label->getContentSize().width, label->getContentSize().height)) };
    bg->addChild(label);
    bg->addChild(trophy);
    this->addChild(bg);
    
    label->setPosition(trophy->getContentSize().width, 0);
    trophy->setPosition(-bg->getContentSize().width / 2, 0);
    
    this->setPosition(WINDOW_CENTER);
    
    return true;
}

// 通知
void TrophyNotification::notify(AnimationCallback callback)
{
    Point toPosition {this->getPosition()};
    this->setPosition(toPosition - Vec2(0, 30.f));
    this->runAction(Spawn::createWithTwoActions(FadeIn::create(0.3f), EaseCubicActionOut::create(MoveTo::create(0.3f, toPosition))));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.3f), CallFunc::create([this, callback]{if(callback) callback(this);})));
}

// 閉じる
void TrophyNotification::close(AnimationCallback callback)
{
    this->runAction(Sequence::createWithTwoActions(Spawn::createWithTwoActions(FadeOut::create(0.3f),
                                                                               EaseCubicActionIn::create(MoveBy::create(0.3f, Vec2(0, -15.f)))),
                                                   CallFunc::create([this, callback]{if(callback) callback(this);})));
}

// 表示時間を取得
float TrophyNotification::getShowingDuration() const { return 5.f; }
