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
#include "Layers/Menu/DungeonMainMenuLayer.h"

#include "Tasks/EventScriptTask.h"
#include "Tasks/ControlMainCharacterTask.h"

#include "MapObjects/Objects.h"

// コンストラクタ
DungeonScene::DungeonScene(){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
    
	CC_SAFE_RELEASE_NULL(this->eventScriptTask);
    CC_SAFE_RELEASE_NULL(this->controlMainCharacterTask);
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
    EventScriptManager::getInstance()->setEventScript(CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::MAP, PlayerDataManager::getInstance()->getLocation().map_id));
    
    if(!baseScene::init(DungeonSceneData::create())) return false;
    //EventScriptManager::getInstance()->setEventScript("TestScript");
    
    // リスナにコールバックを設定
    this->listener->intervalInputCheck = CC_CALLBACK_1(DungeonScene::intervalInputCheck, this);
    this->listener->setInputCheckDelay(Character::DURATION_FOR_ONE_STEP);
    this->listener->setInputCheckInterval(Character::DURATION_FOR_ONE_STEP);
    
    return true;
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished()
{
	FUNCLOG
	
	// 黒い幕を張っておく
	Sprite* black { Sprite::create()};
	black->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	black->setColor(Color3B::BLACK);
	black->setGlobalZOrder(Priority::SCREEN_COVER);
	black->setPosition(WINDOW_CENTER);
	this->addChild(black);
	
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
	mapLayer->setGlobalZOrder(Priority::MAP);
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
	
	// イベントスクリプト処理クラスを生成
	EventScriptTask* eventScriptTask {EventScriptTask::create(this)};
	CC_SAFE_RETAIN(eventScriptTask);
	this->eventScriptTask = eventScriptTask;
    eventScriptTask->runEventScript(0);
    
    // 主人公操作処理クラスを生成
    ControlMainCharacterTask* controlMainCharacterTask {ControlMainCharacterTask::create(this)};
    CC_SAFE_RETAIN(controlMainCharacterTask);
    this->controlMainCharacterTask = controlMainCharacterTask;
    
	// 黒い幕をフェードアウト
	this->runAction(Sequence::create(TargetedAction::create(black, FadeOut::create(0.3f)),
									 TargetedAction::create(black, RemoveSelf::create()),
									 nullptr));
    
    CharacterMessageLayer::Information info1;
    info1.charaName = "いのす";
    info1.pages.push("あいうえを");
    info1.pages.push("かきくけこ\nあsdlj；は；dshfl；あsd；lfはldshf；ぁへf\nあslhfhじゃdbfヵbdf");
    
    CharacterMessageLayer::Information info2;
    info2.charaName = "おぐら";
    info2.pages.push("まんこまんこ");
    
    queue<CharacterMessageLayer::Information> infos {};
    infos.push(info1);
    infos.push(info2);
    
    CharacterMessageLayer* message {CharacterMessageLayer::create(infos)};
    message->setGlobalZOrder(Priority::CHARACTER_MESSAGE);
    this->addChild(message);
    message->start();
    
	return;
}

//EventScriptTaskのrunEventScriptを実行
void DungeonScene::runEvent(int event_id)
{
    if(event_id == MapObject::EventID::UNDIFINED) return;
    this->eventScriptTask->runEventScript(event_id);
    return;
}

// 方向キーを押した時
void DungeonScene::onCursorKeyPressed(const Key& key)
{
    this->controlMainCharacterTask->turn(MapUtils::keyToDirection(key));
}

// スペースキーを押した時
void DungeonScene::onSpaceKeyPressed()
{
    this->controlMainCharacterTask->search();
}

// キーを押し続けている時
void DungeonScene::intervalInputCheck(const vector<Key>& keys)
{
    this->controlMainCharacterTask->walking(MapUtils::keyToDirection(keys));
}

// メニューキー押したとき
void DungeonScene::onMenuKeyPressed()
{
    this->listener->setEnabled(false);
    DungeonMainMenuLayer* menu = DungeonMainMenuLayer::create();
    this->addChild(menu);
    menu->show();
}