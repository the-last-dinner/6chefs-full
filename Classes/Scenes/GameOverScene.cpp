//
//  GameOverScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/02.
//
//

#include "Scenes/GameOverScene.h"

#include "Datas/Scene/GameOverSceneData.h"

// コンストラクタ
GameOverScene::GameOverScene() {FUNCLOG};

// デストラクタ
GameOverScene::~GameOverScene() {FUNCLOG};

// 初期化
bool GameOverScene::init(const Type type)
{
    return BaseScene::init(GameOverSceneData::create());
}

// シーン切り替え完了時
void GameOverScene::onEnter()
{
    BaseScene::onEnter();
}

// リソースのプリロード完了時
void GameOverScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    
}
