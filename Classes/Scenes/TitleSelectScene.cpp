//
//  TitleSelectScene.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/03.
//
//

#include "Scenes/TitleSelectScene.h"

#include "Scenes/OpeningScene.h"
#include "Datas/Scene/TitleSelectSceneData.h"
#include "Layers/LoadingLayer.h"
#include "Layers/TitleSelect/TitleSelectMenuLayer.h"
#include "Managers/TextureManager.h"
#include "Managers/ResourcesManager.h"

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
    // テクスチャーをクリアする
    TextureManager::getInstance()->unloadAllTectures();

    // 選択音
    SoundManager::getInstance()->playSE(Resource::SE::TITLE_ENTER);
    
    // 選択されたタイトルごとに分岐
    switch (titleID) {
        case 0:
            ResourcesManager::getInstance()->setCurrentPath("6chefs");
            break;
        case 1:
            ResourcesManager::getInstance()->setCurrentPath("6chefs2");
            break;
        default:
            // 通常はありえない
            ResourcesManager::getInstance()->setCurrentPath("common");
    }
    Director::getInstance()->replaceScene(OpeningScene::create());
}
