//
//  TitleSelectMenuLayer.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#include "Layers/Menu/TitleSelectMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// 定数
const string TitleSelectMenuLayer::TITLE_NODE_NAME { "title" };
const string TitleSelectMenuLayer::CURSOR_NODE_NAME { "cursor" };
const string TitleSelectMenuLayer::CHARA_NODE_NAME { "chara" };

// コンストラクタ
TitleSelectMenuLayer::TitleSelectMenuLayer() { FUNCLOG }

// デストラクタ
TitleSelectMenuLayer::~TitleSelectMenuLayer() { FUNCLOG }

// 初期化
bool TitleSelectMenuLayer::init(function<void(int)> onSelectTitle)
{
    if (!MenuLayer::init(2, 1)) return false;
    _onSelectTitle = onSelectTitle;
    
    // 背景
    Sprite* bg { Sprite::createWithSpriteFrameName("title_select_bg.png") };
    Size bgSize { bg->getContentSize() };
    bg->setPosition(bgSize.width / 2, bgSize.height / 2);
    this->addChild(bg);
    _bg = bg;
    
    // 2レイヤー
    Layer* layer2 { Layer::create() };
    layer2->setCascadeOpacityEnabled(true);
    this->addChild(layer2);
    _layer2 = layer2;
    
    // 1レイヤー
    Layer* layer1 { Layer::create() };
    layer1->setCascadeOpacityEnabled(true);
    this->addChild(layer1);
    _layer1 = layer1;
    
    this->menuObjects.push_back(_layer1);
    this->menuObjects.push_back(_layer2);
    
    // 1タイトル名
    Sprite* title1 { Sprite::createWithSpriteFrameName("title_select_1.png") };
    title1->setPosition(60, 470);
    title1->setName(TITLE_NODE_NAME);
    layer1->addChild(title1);
    
    // 2タイトル名
    Sprite* title2 { Sprite::createWithSpriteFrameName("title_select_2.png") };
    title2->setPosition(730, 130);
    title2->setName(TITLE_NODE_NAME);
    layer2->addChild(title2);
    
    // 孫一
    Sprite* magoichi { Sprite::createWithSpriteFrameName("title_select_magoichi.png") };
    Size magoSize { magoichi->getContentSize() };
    magoichi->setPosition(magoSize.width / 2 + 80, magoSize.height / 2);
    magoichi->setName(CHARA_NODE_NAME);
    layer1->addChild(magoichi);
    
    // 雪
    Sprite* yuki { Sprite::createWithSpriteFrameName("title_select_yuki.png") };
    Size yukiSize { yuki->getContentSize() };
    yuki->setPosition(yukiSize.width / 2 + 380, yukiSize.height / 2);
    yuki->setName(CHARA_NODE_NAME);
    layer2->addChild(yuki);
    
    // カーソル
    Sprite* cursor1 { Sprite::createWithSpriteFrameName("light.png") };
    cursor1->setBlendFunc(BlendFunc{GL_SRC_COLOR, GL_ONE});
    cursor1->setPosition(title1->getPosition());
    cursor1->setName(CURSOR_NODE_NAME);
    layer1->addChild(cursor1);
    
    Sprite* cursor2 { Sprite::createWithSpriteFrameName("light.png") };
    cursor2->setBlendFunc(BlendFunc{GL_SRC_COLOR, GL_ONE});
    cursor2->setPosition(title2->getPosition());
    cursor2->setName(CURSOR_NODE_NAME);
    layer2->addChild(cursor2);
    
    bg->setOpacity(0);
    layer1->setOpacity(0);
    layer2->setOpacity(0);
    cursor1->setOpacity(0);
    cursor2->setOpacity(0);
    
    return true;
}

// 表示
void TitleSelectMenuLayer::show()
{
    _bg->runAction(FadeIn::create(0.2f));
    _layer1->runAction(Sequence::createWithTwoActions(DelayTime::create(0.2f), FadeIn::create(0.3f)));
    _layer2->runAction(Sequence::createWithTwoActions(DelayTime::create(0.4f), FadeIn::create(0.4f)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.8f), CallFunc::create(CC_CALLBACK_0(TitleSelectMenuLayer::onShowAnimationFinished, this))));
}

// 非表示
void TitleSelectMenuLayer::hide()
{

}

// インデックスが変わった時
// カーソルを移動させたりする
void TitleSelectMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    for (int idx {0}; idx < this->menuObjects.size(); idx++) {
        Node* node { this->menuObjects[newIdx] };
        Node* cursorNode { node->getChildByName(CURSOR_NODE_NAME) };
        if (idx == newIdx) {
            cursorNode->runAction(FadeIn::create(0.2f));
            node->runAction(FadeIn::create(0.2f));
        } else {
            cursorNode->runAction(FadeOut::create(0.1f));
            node->runAction(FadeOut::create(0.1f));
        }
    }
}

// 決定キー押した時
void TitleSelectMenuLayer::onEnterKeyPressed(int idx)
{
    
}

// 表示アニメーション終了時
void TitleSelectMenuLayer::onShowAnimationFinished()
{
    this->listenerKeyboard->setEnabled(true);
    this->onIndexChanged(0, false);
}
