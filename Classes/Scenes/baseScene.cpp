//
//  baseScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "Scenes/baseScene.h"

#include "Layers/LoadingLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

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
	
	// イベントリスナ生成
    EventListenerKeyboardLayer* listenerKeyboard {EventListenerKeyboardLayer::create()};
    listenerKeyboard->onCursorKeyPressed = CC_CALLBACK_1(baseScene::onCursorKeyPressed, this);
    listenerKeyboard->onSpaceKeyPressed = CC_CALLBACK_0(baseScene::onSpaceKeyPressed, this);
    listenerKeyboard->onMenuKeyPressed = CC_CALLBACK_0(baseScene::onMenuKeyPressed, this);
    listenerKeyboard->onDashKeyPressed = CC_CALLBACK_0(baseScene::onDashKeyPressed, this);
    this->addChild(listenerKeyboard);
    this->listenerKeyboard = listenerKeyboard;
	
	// ロード画面レイヤー
	LoadingLayer* loadingLayer = LoadingLayer::create();
	loadingLayer->setLocalZOrder(static_cast<int>(Priority::SCREEN_COVER));
	this->addChild(loadingLayer);
	
	// プリロード開始
	this->data->preloadResources([=](float percentage){if(percentage == 1.f) loadingLayer->loadFinished(CC_CALLBACK_0(baseScene::onPreloadFinished, this));});
	return true;
}