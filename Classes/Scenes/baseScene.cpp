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
	CC_SAFE_RELEASE(this->data);
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
	
	// ロード画面レイヤー
	LoadingLayer* loadingLayer = LoadingLayer::create();
	loadingLayer->setZOrder(100);
	this->addChild(loadingLayer);
	
	// プリロード開始
	this->data->preloadResources([=](float percentage){if(percentage == 1.f) loadingLayer->loadFinished(CC_CALLBACK_0(baseScene::onPreloadFinished, this));});
	return true;
}

// キーを離した時の処理
void baseScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);
	
	return;
}