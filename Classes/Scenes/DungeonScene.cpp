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

#include "Tasks/TaskMediator.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"

// コンストラクタ
DungeonScene::DungeonScene(){FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
    
	CC_SAFE_RELEASE_NULL(this->mediator);
    CC_SAFE_RELEASE_NULL(this->objectList);
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
    
    return baseScene::init(DungeonSceneData::create());
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
    
    // マップレイヤからオブジェクトリストを取り出す
    this->objectList = mapLayer->getMapObjectList();
    CC_SAFE_RETAIN(this->objectList);
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    ambientLightLayer->setGlobalZOrder(Priority::AMBIENT_LIGHT);
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    this->listener->setEnabled(true);
    
    mapLayer->getMainCharacter()->setLight(Light::create(Light::Information(20)), ambientLightLayer);
    
    // タスククラスを生成
    TaskMediator* mediator {TaskMediator::create(this)};
    CC_SAFE_RETAIN(mediator);
    this->mediator = mediator;
    
    // リスナにコールバックを設定
    this->listener->onCursorKeyPressed = CC_CALLBACK_1(TaskMediator::onCursorKeyPressed, this->mediator);
    this->listener->onSpaceKeyPressed = CC_CALLBACK_0(TaskMediator::onSpaceKeyPressed, this->mediator);
    this->listener->intervalInputCheck = CC_CALLBACK_1(TaskMediator::intervalInputCheck, this->mediator);
    this->listener->setInputCheckDelay(Character::DURATION_FOR_ONE_STEP);
    this->listener->setInputCheckInterval(Character::DURATION_FOR_ONE_STEP);
}

// メニューキー押したとき
void DungeonScene::onMenuKeyPressed()
{
    FUNCLOG
    // キーをリリース
    this->listener->releaseKeyAll();
    // スクショ撮る
    RenderTexture* texture = RenderTexture::create(WINDOW_WIDTH, WINDOW_HEIGHT);
    texture->setPosition(WINDOW_CENTER);
    texture->begin();
    this->visit();
    texture->end();
    // ダンジョンメニューシーンをスクショを引数にしてプッシュ
    Director::getInstance()->pushScene(DungeonMenuScene::createScene(texture->getSprite()->getTexture()));
}