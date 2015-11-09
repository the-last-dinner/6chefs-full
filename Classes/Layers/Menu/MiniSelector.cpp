//
//  MiniSelector.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/08.
//
//

#include "Layers/Menu/MiniSelector.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

MiniSelector::MiniSelector(){FUNCLOG}
MiniSelector::~MiniSelector(){FUNCLOG}

bool MiniSelector::init(Selector& selector)
{
    FUNCLOG

    // 必要パラメータ
    Point index = selector.getIndexSize();
    Size size = selector.getWindowSize();
    SpriteUtils::Square square = selector.getPosition();
    SpriteUtils::Margin margin = selector.getMargin();

    // メニュー生成
    if(!MenuLayer::init(index.x, index.y)) return false;
    
    // 下地
    Sprite* rectangle = SpriteUtils::getSquareSprite(square, 0);
    //rectangle->setTextureRect(Rect(0,0,size.width,size.height));
    //rectangle->setPosition(rectangle->getContentSize().width/2, rectangle->getContentSize().height/2);
    rectangle->setColor(selector.getRectangleColor());
    this->addChild(rectangle);
    
     //背景
    Sprite* background = Sprite::create();
    background->setTextureRect(Rect(0,0,size.width - margin.getLeft() - margin.getRight(), size.height - margin.getTop() - margin.getBottom()));
    background->setPosition(size.width/2, size.height/2);
    background->setColor(selector.getBackgroundColor());
    rectangle->addChild(background);
    
    // 選択メニュー
    Size back_size = background->getContentSize();
    const Size panel_size = Size(back_size.width/index.x, back_size.height/index.y);
    const vector<string> menu = selector.getMenu();
    const int menu_size = menu.size();
    for(int i = 0; i < menu_size; i++)
    {
        // 選択パネル
        Sprite* panel = Sprite::create();
        panel->setTextureRect(Rect(0,0,panel_size.width, panel_size.height));
        panel->setPosition(((i%(int)index.x)) * panel_size.width + panel_size.width/2, back_size.height - (floor(i/(int)index.x) + 1) * panel_size.height + panel_size.height/2);
        panel->setColor(selector.getBackgroundColor());
        panel->setTag(i);
        background->addChild(panel);
        // 不透明度を半分にしておく
        panel->setCascadeOpacityEnabled(true);
        panel->setOpacity(100);
        // メニューオブジェクトに登録
        this->menuObjects.push_back(panel);
        
        // 選択ラベル
        Label* label = Label::createWithTTF(menu[i], "fonts/cinecaption2.28.ttf", 24);
        label->setPosition(panel_size.width/2 , panel_size.height / 2);
        label->setColor(Color3B::WHITE);
        panel->addChild(label);
    }
    this->onIndexChanged(0, false);
    return true;
}

// インデックスが変わった時
void MiniSelector::onIndexChanged(int newIdx, bool sound)
{
    if (this->confirm_flag) return;
    if(sound)
    {
        SoundManager::getInstance()->playSE("cursorMove.mp3");
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

// スペースキーが押された時
void MiniSelector::onSpacePressed(int idx){
    if(this->onMiniIndexSelected)
    {
      this->onMiniIndexSelected(idx);
    }
}

// キャンセル時
void MiniSelector::onMenuKeyPressed()
{
    if (this->onMiniSelectorCanceled)
    {
        this->onMiniSelectorCanceled();
    }
}

// 表示
void MiniSelector::show()
{
    this->listenerKeyboard->setEnabled(true);
    this->setVisible(true);
}

// 非表示
void MiniSelector::hide(){
    this->listenerKeyboard->setEnabled(false);
    this->setVisible(false);
}
