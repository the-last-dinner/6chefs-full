//
//  Light.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/13.
//
//

#include "Effects/Light.h"

// 定数
const Color3B Light::TORCH_COLOR {Color3B(195, 110, 60)};

// コンストラクタ
Light::Light()
{ FUNCLOG }

// デストラクタ
Light::~Light()
{ FUNCLOG }

// create関数
Light* Light::create(const cocos2d::Color3B& color, float radius)
{
	Light* p = new(nothrow)Light();
	if (p && p->init(color, radius))
	{
		// オブジェクトを自動メモリ管理へ登録
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

// 初期化
bool Light::init(const Color3B& color, float radius)
{
	if(!Node::init()) return false;
	
	Sprite* light {Sprite::createWithSpriteFrameName("light.png")};
	light->setOpacity(50);
	light->setColor(color);
	float scale {(radius * 2) / light->getContentSize().width};
	light->setScale(scale);
	this->setContentSize(light->getContentSize() * scale);
	
	BlendFunc blend;
	blend.src = GL_SRC_ALPHA;
	blend.dst = GL_ONE;
	
	light->setBlendFunc(blend);
	
	this->addChild(light);
	this->setCascadeOpacityEnabled(true);
	this->setGlobalZOrder(static_cast<int>(Priority::LIGHT));
	
	return true;
}

// 初期化
bool Light::init(float radius)
{
	return this->init(TORCH_COLOR, radius);
}