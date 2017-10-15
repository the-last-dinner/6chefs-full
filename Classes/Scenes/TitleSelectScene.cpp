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
#include "Layers/EventListener/ConfigEventListenerLayer.h"
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
    
    ResourcesManager::getInstance()->setCurrentPath("common");
    ConfigDataManager::getInstance()->setConfigData();
    
    // キーコンフィグを設定できないよう変更
    _configListener->setKeyconfigEnabled(false);
    
    return true;
}

// ロード終了時
void TitleSelectScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    TitleSelectMenuLayer* menuLayer { TitleSelectMenuLayer::create(CC_CALLBACK_1(TitleSelectScene::onTitleSelected, this)) };
    this->addChild(menuLayer);
    loadingLayer->onLoadFinished();
    
    // BGM
    SoundManager::getInstance()->playBGM(ConfigDataManager::getInstance()->getMasterConfigData()->getString(MasterConfigData::TITLE_BGM_FILE), true, 0.7f);
    
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
    SoundManager::getInstance()->stopBGMAll();
    Director::getInstance()->replaceScene(OpeningScene::create());
}
