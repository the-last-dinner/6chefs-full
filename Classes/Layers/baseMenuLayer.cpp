//
//  baseMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "baseMenuLayer.h"

// コンストラクタ
baseMenuLayer::baseMenuLayer():
indexX(0),
indexY(0),
sizeX(0),
sizeY(0),
menuStrings(),
eventListener(nullptr),
moveCursor(),
onSpacePressed()
{FUNCLOG}

// デストラクタ
baseMenuLayer::~baseMenuLayer()
{FUNCLOG}

// 初期化
bool baseMenuLayer::init(const function<void(bool)>& moveCursor, const function<void()>& onSpacePressed)
{
	FUNCLOG
	if(!Layer::init()) return false;
	this->moveCursor = moveCursor;
	this->onSpacePressed = onSpacePressed;
	// イベントリスナ生成。無効にしておく。
	this->eventListener = EventListenerKeyboard::create();
	this->eventListener->onKeyPressed = CC_CALLBACK_1(baseMenuLayer::onKeyPressed, this);
	this->eventListener->onKeyReleased = CC_CALLBACK_1(baseMenuLayer::onKeyReleased, this);
	this->eventListener->setEnabled(false);
	
	// イベントリスナ登録
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->eventListener, this);

	return true;
}

// キーを押した時
void baseMenuLayer::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 押し状態にする
	ActionKeyManager::getInstance()->pressKey(key);
	switch(key)
	{
		case ActionKeyManager::Key::UP:
			this->indexY = (indexY == 0)? indexY = sizeY - 1 : (indexY - 1) % sizeY;
			if(sizeY >= 2)this->moveCursor(true);
			break;
		case ActionKeyManager::Key::DOWN:
			this->indexY = (indexY + 1) % sizeY;
			if(sizeY >= 2)this->moveCursor(true);
			break;
		case ActionKeyManager::Key::SPACE:
			this->onSpacePressed();
			break;
		default:
			break;
	}
	return;
}

// キーを離した時
void baseMenuLayer::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);
	return;
}