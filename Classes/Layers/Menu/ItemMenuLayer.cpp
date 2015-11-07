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
bool ItemMenuLayer::init()
{
    FUNCLOG
    if (!MenuLayer::init(2, 10)) return false;
    
    // 白い背景を生成
    Sprite* white = Sprite::create();
    white->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    white->setColor(Color3B::WHITE);
    white->setPosition(WINDOW_CENTER);
    //white->setOpacity(128);
    this->addChild(white);
    
    // テスト
//    Label* test = Label::createWithTTF("ITEM MENU だよ", "fonts/cinecaption2.28.ttf", 48);
//    test->setPosition(white->getContentSize().width / 2, white->getContentSize().height / 2);
//    test->setColor(Color3B::RED);
//    white->addChild(test);
//    
    // 定義
    SpriteUtils::Square square;
    SpriteUtils::Margin margin;
    // アイテム詳細欄
    square = SpriteUtils::Square(0,0,30,100);
    margin = SpriteUtils::Margin(3, 1.5, 3, 3);
    Sprite* left = SpriteUtils::getSquareSprite(square, margin);
    left->setColor(Color3B::BLACK);
    this->addChild(left);
    
    // 装備欄
    square = SpriteUtils::Square(30,80,100,100);
    margin = SpriteUtils::Margin(3,3,1.5,1.5);
    Sprite* upRight = SpriteUtils::getSquareSprite(square, margin);
    upRight->setColor(Color3B::BLACK);
    this->addChild(upRight);
    
    // アイテムリスト
    square = SpriteUtils::Square(30,0,100,80);
    margin = SpriteUtils::Margin(1.5, 3, 3, 1.5);
    Sprite* item_list = SpriteUtils::getSquareSprite(square, margin);
    item_list->setColor(Color3B::BLACK);
    this->addChild(item_list);
    
    // アイテムリストの中身
    map<int,int> items = PlayerDataManager::getInstance()->getItemAll();
//    int i = 0;
//    for(auto itr = items.begin(); itr != items.end(); itr++)
//    {
//        // パネル生成
//        Sprite* panel = Sprite::create();
//        Size list_size {item_list->getContentSize()};
//        panel->setTextureRect(Rect(0, 0, list_size.width / 2, list_size.height / 6));
//        panel->setColor(Color3B::RED);
//        panel->setPosition((i%2) * (list_size.width / 2) + panel->getContentSize().width, list_size.height - ((int)(i/2) *  (list_size.height/6)));
//        item_list->addChild(panel);
//        
//        // アイテム
//        Label* item = Label::createWithTTF("アイテム" + to_string(i), "fonts/cinecaption2.28.ttf", 48);
//        //Size panel_size {panel->getContentSize()};
//        item->setPosition(item->getContentSize().width/2, item->getContentSize().height/2);
//        item->setColor(Color3B::WHITE);
//        panel->addChild(item);
//        // インクリメント
//        i++;
//    }
    for(int i=0; i<19; i++)
    {
        // パネル生成
        Sprite* panel = Sprite::create();
        Size list_size {item_list->getContentSize()};
        panel->setTextureRect(Rect(0, 0, list_size.width / 2, list_size.height / 10));
        panel->setColor(Color3B::RED);
        panel->setTag(i);
        Size panel_size {panel->getContentSize()};
        panel->setPosition((i%2) * (list_size.width / 2) + panel_size.width/2, list_size.height - ((floor(i/2) + 1)  *  (list_size.height/10)) + panel_size.height/2);
        item_list->addChild(panel);
        // メニューオブジェクトに登録
        this->menuObjects.push_back(panel);
        // 不透明度を半分にしておく
        panel->setCascadeOpacityEnabled(true);
        panel->setOpacity(100);
        
        // アイテム
        Label* item = Label::createWithTTF("アイテム" + to_string(i), "fonts/cinecaption2.28.ttf", 24);
        item->setPosition(item->getContentSize().width/2 + 10 , panel_size.height / 2);
        item->setColor(Color3B::WHITE);
        panel->addChild(item);
    }
    // デフォルトセレクト
    this->onIndexChanged(0, false);
    
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

// スペースキーを押した時
void ItemMenuLayer::onSpacePressed(int idx)
{
    SoundManager::getInstance()->playSound("se/failure.mp3");
}

// 選択対象が変わった時
void ItemMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    if (sound)
    {
        SoundManager::getInstance()->playSound("se/cursorMove.mp3");
    }
    for(Node* obj : this->menuObjects)
    {
        if(obj->getTag() == newIdx)
        {
            obj->runAction(FadeTo::create(0.2f, 255));
        }
        else
        {
            obj->runAction(FadeTo::create(0.2f, 100));
        }
    }
}
