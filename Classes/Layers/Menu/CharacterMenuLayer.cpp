//
//  CharacterMenuLayer.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/09.
//
//

#include "Layers/Menu/CharacterMenuLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

CharacterMenuLayer::CharacterMenuLayer(){FUNCLOG}

CharacterMenuLayer::~CharacterMenuLayer(){FUNCLOG}

// 初期化
bool CharacterMenuLayer::init()
{
    
    if (!MenuLayer::init(2,6)) return false;
    SpriteUtils::Square square;
    SpriteUtils::Margin margin;
    
    // 白い背景を生成
    Sprite* white = Sprite::create();
    white->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    white->setColor(Color3B::WHITE);
    white->setPosition(WINDOW_CENTER);
    //white->setOpacity(128);
    this->addChild(white);
    
    // タイトル
    square = SpriteUtils::Square(0,80,30,100);
    margin = SpriteUtils::Margin(3.0,1.5,1.5,3.0);
    Sprite* leftTop = SpriteUtils::getSquareSprite(square, margin);
    leftTop->setColor(Color3B(128,0,0));
    this->addChild(leftTop);
    
    Label* title = Label::createWithTTF("キャラ", "fonts/cinecaption2.28.ttf", 48);
    title->setPosition(leftTop->getContentSize().width / 2, leftTop->getContentSize().height / 2);
    title->setColor(Color3B::WHITE);
    leftTop->addChild(title);
    return true;
}

// カーソル移動
void CharacterMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    
}

// メニューキー
void CharacterMenuLayer::onMenuKeyPressed()
{
    if (this->onCharacterMenuCanceled)
    {
        this->onCharacterMenuCanceled();
    }
}

// スペースキー
void CharacterMenuLayer::onSpacePressed(int idx)
{
    
}


// 表示
void CharacterMenuLayer::show()
{
    this->listenerKeyboard->setEnabled(true);
    this->setVisible(true);
}

// 非表示
void CharacterMenuLayer::hide()
{
    this->listenerKeyboard->setEnabled(false);
    this->setVisible(false);
}