//
//  StoryMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/08/02.
//
//

#include "Layers/Message/StoryMessageLayer.h"

// コンストラクタ
StoryMessageLayer::StoryMessageLayer()
{FUNCLOG}

// デストラクタ
StoryMessageLayer::~StoryMessageLayer()
{FUNCLOG}

// 初期化
bool StoryMessageLayer::init(const queue<string> pages)
{
	FUNCLOG
	if(!Layer::init()) return false;
	if(!baseMessageLayer::init()) return false;
	
	// ページをセット
	this->setPages(pages);
	
	// 枠を生成
	Sprite* frame = Sprite::create();
	frame->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	frame->setColor(Color3B::BLACK);
	frame->setPosition(WINDOW_CENTER);
	this->setFrame(frame);
	this->addChild(frame);
	
	// ラベルの位置をセット
	this->setHAlignment(TextHAlignment::CENTER);
	
	return true;
}