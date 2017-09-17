//
//  TitleSelectMenuLayer.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#include "Layers/Menu/TitleSelectMenuLayer.h"

// コンストラクタ
TitleSelectMenuLayer::TitleSelectMenuLayer() { FUNCLOG }

// デストラクタ
TitleSelectMenuLayer::~TitleSelectMenuLayer() { FUNCLOG }

// 初期化
bool TitleSelectMenuLayer::init(function<void(int)> onSelectTitle)
{
    if (!MenuLayer::init(2, 1)) return false;
    _onSelectTitle = onSelectTitle;
    Sprite* bg { Sprite::createWithSpriteFrameName("title_select_1.png") };
    Size bgSize { bg->getContentSize() };
    bg->setPosition(bgSize.width / 2, bgSize.height / 2);
    this->addChild(bg);
    return true;
}

// 表示
void TitleSelectMenuLayer::show()
{
    
}

// 非表示
void TitleSelectMenuLayer::hide()
{
    
}

// インデックスが変わった時
// カーソルを移動させたりする
void TitleSelectMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    
}

// 決定キー押した時
void TitleSelectMenuLayer::onEnterKeyPressed(int idx)
{
    
}
