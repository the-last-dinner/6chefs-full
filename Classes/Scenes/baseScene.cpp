//
//  baseScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "baseScene.h"

// コンストラクタ
baseScene::baseScene()
{FUNCLOG}

// デストラクタ
baseScene::~baseScene()
{FUNCLOG}

// シーン共通初期化
bool baseScene::init(SceneData* data, const function<void()>& loadFinished)
{
	FUNCLOG
	if(!Layer::init()) return false;
	// ロード画面レイヤー
	LoadingLayer* loadingLayer = LoadingLayer::create();
	loadingLayer->setZOrder(100);
	this->addChild(loadingLayer);
	
	// プリロード開始
	data->preloadResources([=](float percentage){if(percentage == 1.f) loadingLayer->loadFinished(loadFinished);});
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