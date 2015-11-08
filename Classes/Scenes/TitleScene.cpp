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

#include "Layers/Menu/TitleMainMenuLayer.h"
#include "Layers/Menu/SaveDataSelector.h"

// コンストラクタ
TitleScene::TitleScene(){FUNCLOG}

// デストラクタ
TitleScene::~TitleScene(){FUNCLOG}

// 初期化
bool TitleScene::init()
{
	return baseScene::init(TitleSceneData::create());
}

// リソースロード終了後の処理
void TitleScene::onPreloadFinished()
{
	FUNCLOG
	// メインメニューレイヤーを生成
	TitleMainMenuLayer* mainMenu {TitleMainMenuLayer::create()};
	this->addChild(mainMenu);
	
	// メインメニューのイベントをリッスン
	mainMenu->onStartSelected = CC_CALLBACK_0(TitleScene::onStartSelected, this);
	mainMenu->onContinueSelected = CC_CALLBACK_0(TitleScene::onContinueSelected, this);
	mainMenu->onExitSelected = CC_CALLBACK_0(TitleScene::onExitSelected, this);
	
	mainMenu->show();
	this->mainMenu = mainMenu;
	
	// セーブデータ選択レイヤーを生成
	SaveDataSelector* saveDataSelector { SaveDataSelector::create(false) };
	this->addChild(saveDataSelector);
	
	// セーブデータ選択レイヤーのイベントをリッスン
	saveDataSelector->onSaveDataSelected = CC_CALLBACK_1(TitleScene::onSaveDataSelected, this);
	saveDataSelector->onSaveDataSelectCancelled = CC_CALLBACK_0(TitleScene::onSaveDataSelectCancelled, this);
	
	saveDataSelector->hide();
	this->saveDataSelector = saveDataSelector;
	
	return;
}

// 最初からが選ばれた時
void TitleScene::onStartSelected()
{
	FUNCLOG
	SoundManager::getInstance()->playSound("se/gameStart.mp3");
	SoundManager::getInstance()->unloadAllSounds();
	TextureManager::getInstance()->unloadAllTectures();
	PlayerDataManager::getInstance()->setMainLocalData(0);
    Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocation())));
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
	SoundManager::getInstance()->playSound("se/back.mp3");
	Director::getInstance()->end();
}

// セーブデータが選ばれた時
void TitleScene::onSaveDataSelected(int dataId)
{
	FUNCLOG
	PlayerDataManager::getInstance()->setMainLocalData(dataId);
	Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocation())));
}

// セーブデータ選択をキャンセルした時
void TitleScene::onSaveDataSelectCancelled()
{
	FUNCLOG
	SoundManager::getInstance()->playSound("se/back.mp3");
	this->saveDataSelector->hide();
	this->mainMenu->show();
}