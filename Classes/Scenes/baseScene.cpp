//
//  baseScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "Scenes/baseScene.h"

#include "Layers/LoadingLayer.h"

#include "Datas/Scene/SceneData.h"

// コンストラクタ
baseScene::baseScene(){FUNCLOG}

// デストラクタ
baseScene::~baseScene()
{
	FUNCLOG
	CC_SAFE_RELEASE_NULL(this->data);
}

// シーン共通初期化
bool baseScene::init(SceneData* data)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// データクラスをセットしretain
	this->data = data;
	CC_SAFE_RETAIN(this->data);
	
	// キーステータスを初期化
	ActionKeyManager::getInstance()->initKeyStatus();
	
	// イベントリスナ生成
	EventListenerKeyboard* listenerKeyboard { EventListenerKeyboard::create() };
	listenerKeyboard->onKeyPressed = CC_CALLBACK_1(baseScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_1(baseScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
	listenerKeyboard->setEnabled(false);
	this->listenerKeyboard = listenerKeyboard;
	
	// ロード画面レイヤー
	LoadingLayer* loadingLayer = LoadingLayer::create();
	loadingLayer->setZOrder(static_cast<int>(Priority::SCREEN_COVER));
	this->addChild(loadingLayer);
	
	// プリロード開始
	this->data->preloadResources([=](float percentage){if(percentage == 1.f) loadingLayer->loadFinished(CC_CALLBACK_0(baseScene::onPreloadFinished, this));});
	return true;
}

// キーを押した時

void baseScene::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 押し状態にする
	ActionKeyManager::getInstance()->pressKey(key);

	switch (key) {
		case::ActionKeyManager::Key::UP:
		case::ActionKeyManager::Key::DOWN:
		case::ActionKeyManager::Key::LEFT:
		case::ActionKeyManager::Key::RIGHT:
			this->onCursorKeyPressed(key);
			break;
			
		case::ActionKeyManager::Key::SPACE:
			this->onSpaceKeyPressed();
			break;
			
		case::ActionKeyManager::Key::MENU:
			this->onMenuKeyPressed();
			break;
			
		case::ActionKeyManager::Key::DASH:
			this->onDashKeyPressed();
			break;
			
		default:
			break;
	}
}

// キーを離した時
void baseScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);
}