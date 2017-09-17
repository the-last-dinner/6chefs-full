//
//  TitleSelectScene.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/03.
//
//

#include "Scenes/TitleSelectScene.h"

#include "Datas/Scene/TitleSelectSceneData.h"
#include "Layers/LoadingLayer.h"
#include "Layers/TitleSelect/TitleSelectMenuLayer.h"

// コンストラクタ
TitleSelectScene::TitleSelectScene() { FUNCLOG }

// デストラクタ
TitleSelectScene::~TitleSelectScene() { FUNCLOG }

// 初期化
bool TitleSelectScene::init()
{
    if (!BaseScene::init(TitleSelectSceneData::create())) return false;
    
    return true;
}

// ロード終了時
void TitleSelectScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    TitleSelectMenuLayer* menuLayer { TitleSelectMenuLayer::create(CC_CALLBACK_1(TitleSelectScene::onTitleSelected, this)) };
    this->addChild(menuLayer);
    loadingLayer->onLoadFinished();
    menuLayer->show();
}

// タイトル選択された時
void TitleSelectScene::onTitleSelected(int titleID)
{
    
}
