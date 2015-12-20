//
//  StartUpScene.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/13.
//
//

#include "Scenes/StartUpScene.h"
#include "Scenes/TitleScene.h"
#include "Datas/Scene/StartUpSceneData.h"
#include "Layers/LoadingLayer.h"
#include "Utils/JsonUtils.h"

// 初期化
bool StartUpScene::init()
{
    if (!BaseScene::init(StartUpSceneData::create())) return false;
    
    // セーブデータの生成
    if (!DebugManager::getInstance()->isCryptedSaveData())
    {
        this->encryptSaveFiles();
    }
    PlayerDataManager::getInstance();
    
    // イベントスクリプトの暗号化
    if (!DebugManager::getInstance()->isCryptedEventScript())
    {
        this->enctyptEventScripts();
    }
    
    return true;
}

// シーン生成直後
void StartUpScene::onEnter()
{
    BaseScene::onEnter();
}

// データ読み込み後
void StartUpScene::onPreloadFinished(LoadingLayer *loadingLayer)
{
    // ローディング終了
    loadingLayer->onLoadFinished();
    
    // ロゴ生成
    Sprite* logo {Sprite::createWithSpriteFrameName("the_last_dinner_log.png")};
    logo->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    logo->setScale(1.2f);
    logo->setOpacity(0);
    logo->setZOrder(1000);
    this->addChild(logo);
    
    // 効果音
    SoundManager::getInstance()->playSE("logo_display.mp3", 0.5f);
    
    // ロゴのアニメーション
    logo->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f),EaseCubicActionOut::create(TintTo::create(1.0f, Color3B::RED))));
    
    // シーンのアニメーション
    this->runAction(Sequence::create(DelayTime::create(2.0f), TargetedAction::create(logo,FadeOut::create(1.0f)),CallFunc::create([](){Director::getInstance()->replaceScene(TitleScene::create());}), nullptr));
}

// セーブデータの暗号化
void StartUpScene::encryptSaveFiles()
{
    vector<string> files= {
        "global_template",
        "global",
        "local_template",
        "local1",
        "local2",
        "local3",
        "local4",
        "local5",
        "local6",
        "local7",
        "local8",
        "local9",
        "local10",
    };
    string path = "";
    for (string file : files)
    {
        path = FileUtils::getInstance()->fullPathForFilename("save/" + file + SAVE_EXTENSION);
        if (path != "") LastSupper::JsonUtils::enctyptJsonFile(path);
    }
    DebugManager::getInstance()->setCryptedSaveData();
}

// イベントスクリプトの暗号化
void StartUpScene::enctyptEventScripts()
{
    vector<string> fileNames = CsvDataManager::getInstance()->getMapFileNameAll();
    string path = "";
    for(string file : fileNames)
    {
        path = FileUtils::getInstance()->fullPathForFilename("event/" + file + ES_EXTENSION);
        LastSupper::JsonUtils::enctyptJsonFile(path);
    }
    DebugManager::getInstance()->setCryptedEventScript();
}