//
//  ItemMenuLayer.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/01.
//
//

#include "ItemMenuLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Scenes/DungeonScene.h"

// コンストラクタ
ItemMenuLayer::ItemMenuLayer(){FUNCLOG}

// デストラクタ
ItemMenuLayer::~ItemMenuLayer(){FUNCLOG}

// ItemMenuLayer生成
bool ItemMenuLayer::init(){
    FUNCLOG
    if (!MenuLayer::init(2, 6)) return false;
    
    // 白い背景を生成
    Sprite* white = Sprite::create();
    white->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    white->setColor(Color3B::WHITE);
    white->setPosition(WINDOW_CENTER);
    this->addChild(white);
    
    // テスト
    Label* test = Label::createWithTTF("ITEM MENU だよ", "fonts/cinecaption2.28.ttf", 48);
    test->setPosition(white->getContentSize().width / 2, white->getContentSize().height / 2);
    test->setColor(Color3B::BLACK);
    white->addChild(test);
    return true;
}

// 表示
void ItemMenuLayer::show()
{
    this->listenerKeyboard->setEnabled(true);
    this->setVisible(true);
}

// 非表示
void ItemMenuLayer::hide()
{
    this->listenerKeyboard->setEnabled(false);
    this->setVisible(false);
}

// 戻る
void ItemMenuLayer::onMenuKeyPressed()
{
    FUNCLOG
    if(this->onItemMenuCanceled)
    {
        this->onItemMenuCanceled();
    }
}

void ItemMenuLayer::onSpacePressed(int idx){}
void ItemMenuLayer::onIndexChanged(int newIdx, bool sound){}
