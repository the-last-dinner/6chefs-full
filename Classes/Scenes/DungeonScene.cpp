//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#include "Scenes/DungeonScene.h"

#include "Datas/Scene/DungeonSceneData.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/Message/CharacterMessageLayer.h"

#include "Tasks/EventScriptTask.h"

// コンストラクタ
DungeonScene::DungeonScene(){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
	CC_SAFE_RELEASE_NULL(this->eventScriptTask);
}

// シーン生成
Scene* DungeonScene::createScene()
{
	Scene* scene = Scene::create();
	DungeonScene* layer = DungeonScene::create();
	scene->addChild(layer);
	return scene;
}

// 初期化
bool DungeonScene::init()
{
	FUNCLOG
	
	EventScriptManager::getInstance()->setEventScript("TestScript");
    
	return baseScene::init(DungeonSceneData::create());
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished()
{
	FUNCLOG
	
	// 黒い幕を張っておく
	Sprite* black { Sprite::create()};
	black->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	black->setColor(Color3B::BLACK);
	black->setLocalZOrder(static_cast<int>(Priority::SCREEN_COVER));
	black->setPosition(WINDOW_CENTER);
	this->addChild(black);
	
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
	mapLayer->setLocalZOrder(static_cast<int>(Priority::MAP));
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
	
	// イベントスクリプト処理クラスを生成
	EventScriptTask* eventScriptTask {EventScriptTask::create(this)};
	CC_SAFE_RETAIN(eventScriptTask);
	this->eventScriptTask = eventScriptTask;
    eventScriptTask->runEventScript(3);
    
	// 黒い幕をフェードアウト
	this->runAction(Sequence::create(TargetedAction::create(black, FadeOut::create(0.3f)),
									 TargetedAction::create(black, RemoveSelf::create()),
									 nullptr));
    
    CharacterMessageLayer::Information info1;
    info1.charaName = "いのす";
    info1.pages.push("あいうえを");
    info1.pages.push("かきくけこ");
    
    CharacterMessageLayer::Information info2;
    info2.charaName = "おぐら";
    info2.pages.push("まんこまんこ");
    
    queue<CharacterMessageLayer::Information> infos {};
    infos.push(info1);
    infos.push(info2);
    
    CharacterMessageLayer* message {CharacterMessageLayer::create(infos)};
    this->addChild(message);
    message->start();
    
	return;
}
