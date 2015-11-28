//
//  DungeonCameraScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#include "Scenes/DungeonCameraScene.h"

#include "Datas/Scene/DungeonSceneData.h"

#include "Effects/AmbientLightLayer.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/LoadingLayer.h"

#include "Tasks/CameraTask.h"
#include "Tasks/EventTask.h"

// コンストラクタ
DungeonCameraScene::DungeonCameraScene() { FUNCLOG };

// デストラクタ
DungeonCameraScene::~DungeonCameraScene() { FUNCLOG };

// 初期化
bool DungeonCameraScene::init(DungeonSceneData* data, Vector<GameEvent*> events)
{
    if(!BaseScene::init(data)) return false;
    
    return true;
}

// シーン切り替え終了時
void DungeonCameraScene::onEnter()
{
    BaseScene::onEnter();
}

// プリロード終了時
void DungeonCameraScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    // マップレイヤーを生成
    TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
    mapLayer->setLocalZOrder(Priority::MAP);
    this->addChild(mapLayer);
    this->mapLayer = mapLayer;
    
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
}