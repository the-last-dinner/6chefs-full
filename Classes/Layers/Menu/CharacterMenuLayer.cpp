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
    
}

// カーソル移動
void CharacterMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    
}

// メニューキー
void CharacterMenuLayer::onMenuKeyPressed()
{
    
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