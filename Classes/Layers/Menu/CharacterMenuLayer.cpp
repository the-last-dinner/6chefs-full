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
    
    if (!MenuLayer::init(1,12)) return false;
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
    
    // キャラ紹介
    square = SpriteUtils::Square(0,0,30,80);
    margin = SpriteUtils::Margin(1.5,1.5,3.0,3.0);
    Sprite* leftBottom = SpriteUtils::getSquareSprite(square, margin);
    leftBottom->setColor(Color3B::BLACK);
    leftBottom->setName("charaImage");
    this->addChild(leftBottom);
    
    // キャラ選択部分
    square = SpriteUtils::Square(30,0,100,100);
    margin = SpriteUtils::Margin(3.0,3.0,3.0,1.5);
    Sprite* right = SpriteUtils::getSquareSprite(square, margin);
    right->setColor(Color3B::BLACK);
    this->addChild(right);
    
    Size list_size {right->getContentSize()};
    Point maxSize {Point(1,12)};
    this->characters = CsvDataManager::getInstance()->getDisplayCharacters();
    int chara_count = this->characters.size();
    for (int i=0;i<chara_count; i++){
        // パネル生成
        Sprite* panel = Sprite::create();
        panel->setTextureRect(Rect(0, 0, list_size.width / maxSize.x, list_size.height / maxSize.y));
        panel->setColor(Color3B::BLACK);
        panel->setTag(i);
        Size panel_size {panel->getContentSize()};
        panel->setPosition((i%(int)maxSize.x) * (list_size.width / maxSize.x) + panel_size.width/2, list_size.height - ((floor(i/(int)maxSize.x) + 1)  *  (panel_size.height)) + panel_size.height/2);
        right->addChild(panel);
        // メニューオブジェクトに登録
        this->menuObjects.push_back(panel);
        // 不透明度を半分にしておく
        panel->setCascadeOpacityEnabled(true);
        panel->setOpacity(100);
        
        // キャラクター名
        Label* chara = Label::createWithTTF(CsvDataManager::getInstance()->getCharaName(this->characters[i]), "fonts/cinecaption2.28.ttf", 24);
        chara->setPosition(panel_size.width/2 , panel_size.height / 2);
        chara->setColor(Color3B::WHITE);
        panel->addChild(chara);
    }
    
    // デフォルトセット
    onIndexChanged(0, false);
    
    return true;
}

// カーソル移動
void CharacterMenuLayer::onIndexChanged(int newIdx, bool sound)
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
    // キャラクターイメージを変更
    this->changeCharaImage(newIdx);
}

void CharacterMenuLayer::changeCharaImage(const int idx)
{
    // 親のスプライトを取得
    Node* leftBottom = this->getChildByName("charaImage");
    // 子のスプライトがすでに存在すれば消してから生成
    string labelName = "imgLabel";
    if (leftBottom->getChildByName(labelName)){
        leftBottom->removeChildByName(labelName);
    }
    Size panel = leftBottom->getContentSize();
    string fileName = CsvDataManager::getInstance()->getCharaFileName(this->characters[idx]) + "_s_0.png";
    if(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName))
    {
        Sprite* img { Sprite::createWithSpriteFrameName(fileName)};
        img->setScale(0.30);
        img->setPosition(panel.width/2,panel.height/2 + 20);
        img->setName(labelName);
        //img->setLocalZOrder(-1);
        leftBottom->addChild(img);
    }
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