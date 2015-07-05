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