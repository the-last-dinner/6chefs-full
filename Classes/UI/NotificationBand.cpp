//
//  NotificationBand.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/11/27.
//
//

#include "UI/NotificationBand.h"

bool NotificationBand::init(const string& message)
{
    if (!Node::init()) return false;
    
    // メッセージ表示帯
    Sprite* band = Sprite::create();
    band->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/4));
    band->setColor(Color3B::BLACK);
    band->setPosition(WINDOW_CENTER);
    band->setScaleY(0.1f);
    band->setOpacity(0);
    band->runAction(FadeIn::create(0.2f));
    band->runAction(EaseCubicActionOut::create(ScaleTo::create(0.5f, 1.f)));
    this->addChild(band);
    this->band = band;
    
    // 完了メッセージラベル
    Label* messageLabel = Label::createWithTTF(message, "fonts/cinecaption2.28.ttf", band->getContentSize().height / 5);
    messageLabel->setPosition(Point(messageLabel->getContentSize().width / 2 + (WINDOW_WIDTH - messageLabel->getContentSize().width)/2, band->getContentSize().height / 2));
    messageLabel->setOpacity(0);
    messageLabel->runAction(FadeIn::create(0.4f));
    band->addChild(messageLabel);
    this->messageLabel = messageLabel;
    
    return true;
}

// 帯の色を変更
void NotificationBand::setBandColor(const Color3B &color)
{
    this->band->setColor(color);
}

// メッセージの色を変更
void NotificationBand::setMessageColor(const Color3B &color)
{
    this->messageLabel->setColor(color);
}