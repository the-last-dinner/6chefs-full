//
//  Cloud.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#include "UI/Cloud.h"

#include "cocos-ext.h"

// コンストラクタ
Cloud::Cloud() {FUNCLOG};

// デストラクタ
Cloud::~Cloud() {FUNCLOG};

// 初期化
bool Cloud::init(const Size& size)
{
    if(!Node::init()) return false;
    
    // カスケード
    this->setCascadeColorEnabled(true);
    this->setCascadeOpacityEnabled(true);
    
    Sprite* sprite { Sprite::createWithSpriteFrameName("cloud.png") };
    this->addChild(sprite);
    
    // 最小サイズ
    this->setScale(size.width / sprite->getContentSize().width);
    
    return true;
}