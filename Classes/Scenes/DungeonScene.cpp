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

#include "Tasks/EventTask.h"
#include "Tasks/CameraTask.h"
#include "Tasks/PlayerControlTask.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"

#include "Event/EventScript.h"

// コンストラクタ
DungeonScene::DungeonScene():fu(FileUtils::getInstance()){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
    
    CC_SAFE_RELEASE_NULL(this->cameraTask);
	CC_SAFE_RELEASE_NULL(this->eventTask);
    CC_SAFE_RELEASE_NULL(this->playerControlTask);
}

// 初期化
bool DungeonScene::init(DungeonSceneData* data)
{
    return baseScene::init(data);
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished()
{
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
	mapLayer->setGlobalZOrder(Priority::MAP);
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    ambientLightLayer->setGlobalZOrder(Priority::AMBIENT_LIGHT);
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    // カメラ処理クラス生成
    CameraTask* cameraTask {CameraTask::create()};
    CC_SAFE_RETAIN(cameraTask);
    this->cameraTask = cameraTask;
    
    // イベント処理クラス生成
    EventTask* eventTask { EventTask::create() };
    CC_SAFE_RETAIN(eventTask);
    this->eventTask = eventTask;
    
    // プレイヤー操作処理クラス生成
    PlayerControlTask* playerControlTask {PlayerControlTask::create()};
    CC_SAFE_RETAIN(playerControlTask);
    this->playerControlTask = playerControlTask;
    
    // リスナにコールバックを設定
    this->listener->onCursorKeyPressed = CC_CALLBACK_1(PlayerControlTask::turn, playerControlTask);
    this->listener->onSpaceKeyPressed = CC_CALLBACK_0(PlayerControlTask::search, playerControlTask);
    this->listener->intervalInputCheck = CC_CALLBACK_1(PlayerControlTask::walking, playerControlTask);
    this->listener->setInputCheckDelay(Character::DURATION_FOR_ONE_STEP);
    this->listener->setInputCheckInterval(Character::DURATION_FOR_ONE_STEP);
    
    this->listener->setEnabled(true);
    
    mapLayer->getMapObjectList()->getMainCharacter()->setLight(Light::create(Light::Information(20)), ambientLightLayer);
}

// メニューキー押したとき
void DungeonScene::onMenuKeyPressed()
{
    this->listener->setEnabled(false);
    // 主人公の位置をセット
    Character* chara = this->mapLayer->getMapObjectList()->getMainCharacter();
    Point point = chara->getGridPosition(this->mapLayer->getMapSize());
    Direction dir = chara->getDirection();
    PlayerDataManager::Location location{PlayerDataManager::getInstance()->getLocation().map_id, static_cast<int>(point.x), static_cast<int>(point.y), dir};
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

// イベントリスナを取得
EventListenerKeyboardLayer* DungeonScene::getListener() const
{
    return this->listener;
}