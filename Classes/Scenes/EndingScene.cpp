//
//  EndingScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/03.
//
//

#include "Scenes/EndingScene.h"

#include "Datas/Scene/EndingSceneData.h"

// コンストラクタ
EndingScene::EndingScene() {FUNCLOG};

// デストラクタ
EndingScene::~EndingScene() {FUNCLOG};

// 初期化
bool EndingScene::init(const int endingId)
{
    return BaseScene::init(EndingSceneData::create());
}

// シーン切り替え終了時
void EndingScene::onEnter()
{
    BaseScene::onEnter();
}

// リソースのプリロード完了時
void EndingScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    
}