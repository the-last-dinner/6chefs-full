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
menuObjects{},
eventListener(nullptr)
{FUNCLOG}

// デストラクタ
baseMenuLayer::~baseMenuLayer()
{FUNCLOG}

// 初期化
bool baseMenuLayer::init(int sizeX, int sizeY)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// メニューの項目数を設定
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	
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
		case ActionKeyManager::Key::LEFT:
			this->indexX = (indexX == 0)? indexX = sizeX - 1 : (indexX - 1) % sizeX;
			if(sizeX >= 2)this->moveCursor(true);
			break;
		case ActionKeyManager::Key::RIGHT:
			this->indexX = (indexX + 1) % sizeX;
			if(sizeX >= 2)this->moveCursor(true);
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
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);
	return;
}

// 現在選ばれているメニューのINDEXを取得(現時点では横優先配置の場合のみ)
int baseMenuLayer::getSelectedIndex()
{return sizeX * indexY + indexX;}

// メニューサイズの横方向を取得
int baseMenuLayer::getMenuSizeX()
{return this->sizeX;}

// メニューサイズの縦方向を取得
int baseMenuLayer::getMenuSizeY()
{return this->sizeY;}