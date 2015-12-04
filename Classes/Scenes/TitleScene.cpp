//
//  TitleScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "Scenes/TitleScene.h"
#include "Scenes/DungeonScene.h"

#include "Datas/Scene/TitleSceneData.h"
#include "Datas/Scene/DungeonSceneData.h"

#include "Layers/LoadingLayer.h"
#include "Layers/Menu/SaveDataSelector.h"
#include "Layers/Menu/TitleMainMenuLayer.h"
#include "Layers/Menu/TrophyListLayer.h"
#include "Models/GlobalPlayerData.h"

// コンストラクタ
TitleScene::TitleScene(){FUNCLOG}

// デストラクタ
TitleScene::~TitleScene(){FUNCLOG}

// 初期化
bool TitleScene::init()
{
    if(!BaseScene::init(TitleSceneData::create())) return false;
    
    return true;
}

// シーン切り替え完了時
void TitleScene::onEnter()
{
    BaseScene::onEnter();
}

// リソースロード終了後の処理
void TitleScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    // ローディング終了
    loadingLayer->onLoadFinished();
    
    // メインメニューレイヤーを生成
    TitleMainMenuLayer* mainMenu {TitleMainMenuLayer::create()};
    this->addChild(mainMenu);
    
    // メインメニューのイベントをリッスン
    mainMenu->onStartSelected = CC_CALLBACK_0(TitleScene::onStartSelected, this);
    mainMenu->onContinueSelected = CC_CALLBACK_0(TitleScene::onContinueSelected, this);
    mainMenu->onExitSelected = CC_CALLBACK_0(TitleScene::onExitSelected, this);
    mainMenu->onTrophySelected = CC_CALLBACK_0(TitleScene::onTrophyListSelected, this);
    
    mainMenu->show();
    this->mainMenu = mainMenu;
    
    // セーブデータ選択レイヤーを生成
    SaveDataSelector* saveDataSelector { SaveDataSelector::create(false) };
    this->addChild(saveDataSelector);
    
    // セーブデータ選択レイヤーのイベントをリッスン
    saveDataSelector->onSaveDataSelected = CC_CALLBACK_1(TitleScene::onSaveDataSelected, this);
    saveDataSelector->onSaveDataSelectCancelled = CC_CALLBACK_0(TitleScene::onSaveDataSelectCancelled, this);
    saveDataSelector->setVisible(false);
    saveDataSelector->hide();
    this->saveDataSelector = saveDataSelector;
}

// 最初からが選ばれた時
void TitleScene::onStartSelected()
{
	FUNCLOG
	SoundManager::getInstance()->playSE("gameStart.mp3");
	SoundManager::getInstance()->unloadAllSounds();
	//TextureManager::getInstance()->unloadAllTectures();
	PlayerDataManager::getInstance()->setGameStart(0);
    Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocalData()->getLocation())));
}

// 続きからが選ばれた時
void TitleScene::onContinueSelected()
{
	FUNCLOG
	this->mainMenu->hide();
	this->saveDataSelector->show();
}

// 終了が選ばれた時
void TitleScene::onExitSelected()
{
	FUNCLOG
	SoundManager::getInstance()->playSE("back.mp3");
	Director::getInstance()->end();
}

// セーブデータが選ばれた時
void TitleScene::onSaveDataSelected(int dataId)
{
	FUNCLOG
	PlayerDataManager::getInstance()->setGameStart(dataId);
	Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocalData()->getLocation())));
}

// セーブデータ選択をキャンセルした時
void TitleScene::onSaveDataSelectCancelled()
{
	FUNCLOG
	SoundManager::getInstance()->playSE("back.mp3");
	this->saveDataSelector->hide();
	this->mainMenu->show();
}

#pragma mark -
#pragma mark TrophyListLayer

// トロフィーリストを生成
void TitleScene::createTrophyListLayer()
{
    TrophyListLayer* trophyList {TrophyListLayer::create()};
    trophyList->onTrophyListCanceled = CC_CALLBACK_0(TitleScene::onTrophyListCanceled, this);
    trophyList->setVisible(false);
    this->addChild(trophyList);
    this->trophyList = trophyList;
}

// トロフィーリストを選択した時
void TitleScene::onTrophyListSelected()
{
    if (!PlayerDataManager::getInstance()->getGlobalData()->isCleared())
    {
        SoundManager::getInstance()->playSE("failure.mp3");
        return;
    }
    if(!this->trophyList)
    {
        this->createTrophyListLayer();
    }
    this->mainMenu->hide();
    this->trophyList->show();
}

// トロフィーリストをキャンセル時
void TitleScene::onTrophyListCanceled()
{
    SoundManager::getInstance()->playSE("back.mp3");
    this->trophyList->hide();
    this->mainMenu->show();
}

