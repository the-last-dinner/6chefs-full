//
//  CharacterMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "CharacterMessageLayer.h"

// コンストラクタ
CharacterMessageLayer::CharacterMessageLayer()
{FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer()
{FUNCLOG}

// 初期化
bool CharacterMessageLayer::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	// 枠を生成
	baseMessageLayer::base = Sprite::create();
	baseMessageLayer::base->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	baseMessageLayer::base->setColor(Color3B::BLACK);
	// baseMessageLayer::base->setOpacity(0.7f);
	
	// 枠を配置
	baseMessageLayer::base->setPosition(base->getContentSize() / 2);
	this->addChild(baseMessageLayer::base);
	
	return true;
}