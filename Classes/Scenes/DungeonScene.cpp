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
#include "Layers/Message/CharacterMessageLayer.h"

#include "Tasks/EventScriptTask.h"
#include "Tasks/ControlMainCharacterTask.h"
#include "Tasks/CameraTask.h"

#include "MapObjects/Objects.h"

// コンストラクタ
DungeonScene::DungeonScene():fu(FileUtils::getInstance()){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
    
    this->cameraTask->stopFollowing();
    
	CC_SAFE_RELEASE_NULL(this->eventScriptTask);
    CC_SAFE_RELEASE_NULL(this->controlMainCharacterTask);
    CC_SAFE_RELEASE_NULL(this->cameraTask);
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
    
    // イベントスクリプト処理クラスを生成
    EventScriptTask* eventScriptTask {EventScriptTask::create(this)};
    CC_SAFE_RETAIN(eventScriptTask);
    this->eventScriptTask = eventScriptTask;
    eventScriptTask->runEventScript(0);
    
    // 主人公操作処理クラスを生成
    ControlMainCharacterTask* controlMainCharacterTask {ControlMainCharacterTask::create(this)};
    CC_SAFE_RETAIN(controlMainCharacterTask);
    this->controlMainCharacterTask = controlMainCharacterTask;
    
    // リスナにコールバックを設定
    this->listener->intervalInputCheck = CC_CALLBACK_1(DungeonScene::intervalInputCheck, this);
    this->listener->setInputCheckDelay(Character::DURATION_FOR_ONE_STEP);
    this->listener->setInputCheckInterval(Character::DURATION_FOR_ONE_STEP);
    
    this->listener->setEnabled(false);
    
    return true;
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished()
{
	FUNCLOG
	
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
	mapLayer->setGlobalZOrder(Priority::MAP);
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
    
    // カメラ処理クラスを生成
    CameraTask* cameraTask {CameraTask::create(this)};
    CC_SAFE_RETAIN(cameraTask);
    this->cameraTask = cameraTask;
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    ambientLightLayer->setGlobalZOrder(Priority::AMBIENT_LIGHT);
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    this->listener->setEnabled(true);
    
    mapLayer->getMainCharacter()->setLight(Light::create(Light::Information(20)), ambientLightLayer);
    
    this->cameraTask->setTarget(mapLayer->getMainCharacter());
    
	return;
}

//EventScriptTaskのrunEventScriptを実行
void DungeonScene::runEvent(int event_id)
{
    if(event_id == static_cast<int>(EventID::UNDIFINED)) return;
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
    FUNCLOG
    // キーをリリース
    this->listener->releaseKeyAll();
    // スクショをとって、ダンジョンメニューシーンをプッシュ
    string path = LastSupper::StringUtils::strReplace("global.json", "screen0.png", fu->FileUtils::fullPathForFilename("save/global.json"));
    cout << "path>>" << path << endl;
    utils::captureScreen([=](bool success, string filename){
     if(success)
     {
         Sprite* screen = Sprite::create(filename);
         Director::getInstance()->pushScene(DungeonMenuScene::createScene(screen->getTexture()));
         Director::getInstance()->getTextureCache()->removeTextureForKey(filename);
     }
    }, path);
}