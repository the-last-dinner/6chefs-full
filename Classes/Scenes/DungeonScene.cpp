//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#include "Scenes/DungeonScene.h"
#include "Scenes/DungeonMenuScene.h"

#include "Datas/Scene/DungeonSceneData.h"

#include "Effects/AmbientLightLayer.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Layers/LoadingLayer.h"

#include "Tasks/EventTask.h"
#include "Tasks/CameraTask.h"
#include "Tasks/PlayerControlTask.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

// コンストラクタ
DungeonScene::DungeonScene():fu(FileUtils::getInstance()){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->party);
}

// 初期化
bool DungeonScene::init(DungeonSceneData* data)
{
    if(!Scene::init()) return false;
    
    // データクラスをセットしretain
    this->data = data;
    CC_SAFE_RETAIN(this->data);
    
    // ロード画面レイヤ
    LoadingLayer* loadingLayer = LoadingLayer::create();
    loadingLayer->setLocalZOrder(Priority::LOADING_LAYER);
    this->addChild(loadingLayer);
    this->loadingLayer = loadingLayer;
    
    // プリロード開始
    this->data->preloadResources([=](float percentage){if(percentage == 1.f) this->runAction(Sequence::createWithTwoActions(DelayTime::create(1.f), CallFunc::create([this]{this->onPreloadFinished();})));});
    
    return true;
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished()
{
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
    mapLayer->setLocalZOrder(Priority::MAP);
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
    
    // 主人公一行を生成
    Party* party { this->createParty() };
    this->party = party;
    
    // 主人公一行をマップに配置
    mapLayer->setParty(party);
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    ambientLightLayer->setLocalZOrder(Priority::AMBIENT_LIGHT);
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    // カメラ処理クラス生成
    CameraTask* cameraTask {CameraTask::create()};
    this->addChild(cameraTask);
    this->cameraTask = cameraTask;
    
    // イベント処理クラス生成
    EventTask* eventTask { EventTask::create() };
    this->addChild(eventTask);
    this->eventTask = eventTask;
    
    // プレイヤー操作処理クラス生成
    PlayerControlTask* playerControlTask {PlayerControlTask::create()};
    this->addChild(playerControlTask);
    this->playerControlTask = playerControlTask;
    
    // イベントリスナ生成
    EventListenerKeyboardLayer* listener { EventListenerKeyboardLayer::create() };
    listener->onCursorKeyPressed = [playerControlTask, party](const Key& key){playerControlTask->turn(key, party);};
    listener->onSpaceKeyPressed = [playerControlTask, party]{playerControlTask->search(party);};
    listener->onMenuKeyPressed = CC_CALLBACK_0(DungeonScene::onMenuKeyPressed, this);
    
    this->addChild(listener);
    this->listener = listener;
    
    // Trigger::INITを実行
    eventTask->runEvent(mapLayer->getMapObjectList()->getEventIds(Trigger::INIT), CC_CALLBACK_0(DungeonScene::onInitEventFinished, this));
}

// Trigger::INITのイベント実行後
void DungeonScene::onInitEventFinished()
{
    this->party->getMainCharacter()->setLight(Light::create(Light::Information(20)), ambientLightLayer);
    cameraTask->setTarget( this->party->getMainCharacter() );
    
    // ローディングレイヤを消す
    this->loadingLayer->loadFinished();
    
    // Trigger::AFTER_INITを実行
    this->eventTask->runEvent(mapLayer->getMapObjectList()->getEventIds(Trigger::AFTER_INIT));
}

// 主人公一行を生成
Party* DungeonScene::createParty()
{
    Party* party { Party::create(PlayerDataManager::getInstance()->getPartyMemberAll()) };
    CC_SAFE_RETAIN(party);
    
    return party;
}

// メニューキー押したとき
void DungeonScene::onMenuKeyPressed()
{
    this->listener->setEnabled(false);
    // 主人公の位置をセット
    Character* chara = this->party->getMainCharacter();
    Point point = chara->getGridPosition();
    Direction dir = chara->getDirection();
    Location location{PlayerDataManager::getInstance()->getLocation().map_id, static_cast<int>(point.x), static_cast<int>(point.y), dir};
    PlayerDataManager::getInstance()->setLocation(location);
    // スクショをとって、ダンジョンメニューシーンをプッシュ
    string path = LastSupper::StringUtils::strReplace("global.json", "screen0.png", fu->FileUtils::fullPathForFilename("save/global.json"));
    utils::captureScreen([=](bool success, string filename){
     if(success)
     {
         Sprite* screen = Sprite::create(filename);
         Scene* menu = DungeonMenuScene::create(screen->getTexture(), [=](){this->listener->setEnabled(true);});
         // メニューシーンをプッシュ
         Director::getInstance()->pushScene(menu);
         // cache削除
         Director::getInstance()->getTextureCache()->removeTextureForKey(filename);
     }
    }, path);
}

// データクラスを取得
DungeonSceneData* DungeonScene::getData() const
{
    return dynamic_cast<DungeonSceneData*>(this->data);
}