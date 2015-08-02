//
//  SystemMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "SystemMessageLayer.h"

// コンストラクタ
SystemMessageLayer::SystemMessageLayer()
{FUNCLOG}

// デストラクタ
SystemMessageLayer::~SystemMessageLayer()
{FUNCLOG}

// create関数
SystemMessageLayer* SystemMessageLayer::createWithPages(const queue<string>& pages)
{
	SystemMessageLayer* pRet = new(nothrow)SystemMessageLayer();
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
bool SystemMessageLayer::init(const queue<string>& pages)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// ページをセット
	this->setPages(pages);
	
	// 枠を生成
	Sprite* frame = Sprite::create();
	frame->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	frame->setColor(Color3B::BLACK);
	frame->setPosition(WINDOW_CENTER);
	this->setFrame(frame);
	this->addChild(frame);
	
	// メッセージの表示位置をセット
	this->setMessagePosition(frame->getContentSize() / 2);
	
	return true;
}