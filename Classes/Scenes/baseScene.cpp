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
baseScene::baseScene(){}

// デストラクタ
baseScene::~baseScene()
{
	CC_SAFE_RELEASE_NULL(this->data);
}

// シーン共通初期化
bool baseScene::init(SceneData* data)
{
	if(!Scene::init()) return false;
	
	// データクラスをセットしretain
	this->data = data;
	CC_SAFE_RETAIN(this->data);
    
	return true;
}

// シーンの切り替え完了時
void baseScene::onEnter()
{
    Scene::onEnter();
    
    // ロード画面レイヤー
    LoadingLayer* loadingLayer = LoadingLayer::create();
    loadingLayer->setGlobalZOrder(Priority::SCREEN_COVER);
    this->addChild(loadingLayer);
    
    // プリロード開始
    this->data->preloadResources([this, loadingLayer](float percentage)
    {
        if(percentage == 1.f)
        {
            // プリロード完了時にコールバック
            this->onPreloadFinished(loadingLayer);
        }
    });
}
