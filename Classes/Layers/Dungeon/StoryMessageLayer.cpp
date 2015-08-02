//
//  StoryMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/08/02.
//
//

#include "StoryMessageLayer.h"

// コンストラクタ
StoryMessageLayer::StoryMessageLayer()
{FUNCLOG}

// デストラクタ
StoryMessageLayer::~StoryMessageLayer()
{FUNCLOG}

// create関数
StoryMessageLayer* StoryMessageLayer::createWithPages(const queue<string>& pages)
{
	StoryMessageLayer* pRet = new(nothrow)StoryMessageLayer();
	if (pRet && pRet->init(pages))
	{
		// オブジェクトを自動メモリ管理へ登録
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	return nullptr;
}

// 初期化
bool StoryMessageLayer::init(const queue<string>& pages)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
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
	this->setMessagePosition(frame->getContentSize() / 2);
	this->setHAlignment(TextHAlignment::CENTER);
	
	return true;
}