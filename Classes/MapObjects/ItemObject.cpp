//
//  ItemObject.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#include "MapObjects/ItemObject.h"

// 定数
const string ItemObject::PREFIX { "item_" };
const string ItemObject::BLUE {"blue_"};
const int ItemObject::ANIMATION_FRAME_NUM { 3 };
const float ItemObject::ANIMATION_DELAY_PER_UNIT { 0.3f };

// コンストラクタ
ItemObject::ItemObject() {FUNCLOG};

// デストラクタ
ItemObject::~ItemObject() {FUNCLOG};

// 初期化
bool ItemObject::init()
{
    if(!MapObject::init()) return false;
    
    // アイテムSpriteを生成
    Sprite* sprite { Sprite::createWithSpriteFrameName(this->getSpriteFrameName(0)) };
    this->addChild(sprite);
    
    // 輝きアニメーション生成
    Animation* animation { Animation::create() };
    
    for(int i {0}; i < ANIMATION_FRAME_NUM; i++)
    {
        animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->getSpriteFrameName(i)));
    }
    
    animation->setDelayPerUnit(ANIMATION_DELAY_PER_UNIT);
    
    Animate* animate { Animate::create(animation) };
    
    // アニメーション開始
    sprite->runAction(RepeatForever::create(animate));
    
    return true;
}

string ItemObject::getSpriteFrameName(int state)
{
    return PREFIX + BLUE + to_string(state) + ".png";
}
