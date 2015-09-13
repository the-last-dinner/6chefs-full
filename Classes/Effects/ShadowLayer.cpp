//
//  ShadowLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/10.
//
//

#include "Effects/ShadowLayer.h"

// コンストラクタ
ShadowLayer::ShadowLayer(){ FUNCLOG }

// デストラクタ
ShadowLayer::~ShadowLayer(){ FUNCLOG }

// 初期化
bool ShadowLayer::init(const Color4B& color)
{
	if(!Layer::init()) return false;
	
	Sprite* shadow { Sprite::create()};
	shadow->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	shadow->setColor(Color3B(color));
	shadow->setPosition(WINDOW_CENTER);
	shadow->setOpacity(color.a);
	this->addChild(shadow);
	this->setCascadeOpacityEnabled(true);
	
    return true;
}
