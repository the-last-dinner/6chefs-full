//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#include "Scenes/DungeonScene.h"

#include "Datas/Scene/DungeonSceneData.h"

#include "Effects/AmbientLightLayer.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Layers/LoadingLayer.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"

#include "Models/Stamina.h"

#include "Scenes/DungeonMenuScene.h"
#include "Scenes/TitleScene.h"

#include "Tasks/EnemyTask.h"
#include "Tasks/CameraTask.h"
#include "Tasks/EventTask.h"
#include "Tasks/PlayerControlTask.h"

#include "UI/StaminaBar.h"

// コンストラクタ
DungeonScene::DungeonScene() {FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->party);
}

// 初期化
bool DungeonScene::init(DungeonSceneData* data)
{
    if(!BaseScene::init(data)) return false;
    
    return true;
}

// シーン切り替え終了時
void DungeonScene::onEnter()
{
    BaseScene::onEnter();
    
    // フェード用カバー
    Sprite* cover {DungeonSceneManager::getInstance()->getCover()};
    
    if(!cover) return;
    
    cover->removeFromParent();
    this->addChild(cover);
}

// リソースプリロード完了時の処理
void DungeonScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
	// マップレイヤーを生成
	TiledMapLayer* mapLayer {TiledMapLayer::create(PlayerDataManager::getInstance()->getLocation())};
    mapLayer->setLocalZOrder(Priority::MAP);
	this->addChild(mapLayer);
	this->mapLayer = mapLayer;
    
    // 主人公一行を生成
    Party* party { Party::create(PlayerDataManager::getInstance()->getPartyMemberAll()) };
    CC_SAFE_RETAIN(party);
    this->party = party;
    
    // 主人公一行をマップに配置
    mapLayer->setParty(party);
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    ambientLightLayer->setLocalZOrder(Priority::AMBIENT_LIGHT);
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    // 敵処理クラス生成
    EnemyTask* enemyTask { EnemyTask::create() };
    this->addChild(enemyTask);
    this->enemyTask = enemyTask;
    
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
    
    // スタミナバー生成
    StaminaBar* staminaBar { StaminaBar::create() };
    staminaBar->setLocalZOrder(Priority::STAMINA_BAR);
    this->addChild(staminaBar);
    this->staminaBar = staminaBar;
    
    // スタミナが変化した際のコールバック指定
    DungeonSceneManager::getInstance()->setStaminaCallback(CC_CALLBACK_1(StaminaBar::setPercentage, staminaBar));
    
    // スタミナ残量を反映
    staminaBar->setPercentage(DungeonSceneManager::getInstance()->getStamina()->getPercentage());
    
    // 敵が存在すれば、スタミナバーを表示しておく
    if(enemyTask->existsEnemy()) staminaBar->slideIn();
    
    // コールバック設定
    eventTask->onRunEvent = [playerControlTask, party]{playerControlTask->setControlEnable(false, party);};
    eventTask->onAllEventFinished = [playerControlTask, party]{playerControlTask->setControlEnable(true, party);};
    
    // イベントリスナ生成
    EventListenerKeyboardLayer* listener { EventListenerKeyboardLayer::create() };
    listener->onCursorKeyPressed = [playerControlTask, party](const Key& key){playerControlTask->turn(key, party);};
    listener->onSpaceKeyPressed = [playerControlTask, party]{playerControlTask->search(party);};
    listener->onMenuKeyPressed = CC_CALLBACK_0(DungeonScene::onMenuKeyPressed, this);
    
    this->addChild(listener);
    this->listener = listener;
    
    // Trigger::INITを実行
    eventTask->runEvent(mapLayer->getMapObjectList()->getEventIds(Trigger::INIT), [this, loadingLayer](){this->onInitEventFinished(loadingLayer);});
}

// Trigger::INITのイベント実行後
void DungeonScene::onInitEventFinished(LoadingLayer* loadingLayer)
{
    this->party->getMainCharacter()->setLight(Light::create(Light::Information(20)), ambientLightLayer);
    cameraTask->setTarget( this->party->getMainCharacter() );
    
    this->enemyTask->start(PlayerDataManager::getInstance()->getLocation().map_id);
    
    // ローディング終了
    loadingLayer->onLoadFinished();
    
    // Trigger::AFTER_INITを実行
    this->eventTask->runEvent(this->mapLayer->getMapObjectList()->getEventIds(Trigger::AFTER_INIT), CC_CALLBACK_0(DungeonScene::onAfterInitEventFinished, this));
}

// Trigger::AFTER_INITのイベント終了時
void DungeonScene::onAfterInitEventFinished()
{
    this->eventTask->runEvent(this->getData()->getInitialEventId());
}

// メニューキー押したとき
void DungeonScene::onMenuKeyPressed()
{
    // イベント中なら無視
    if(this->eventTask->isEventRunning() || this->eventTask->existsEvent()) return;
    
    // 敵が存在すれば無視
    if(this->enemyTask->existsEnemy()) return;
    
    // リスナーを停止
    this->listener->setEnabled(false);
    DungeonSceneManager::getInstance()->pauseStopWatch(); // カウントダウンしてれば停止
    
    // 主人公の位置をセット
    Character* chara = this->party->getMainCharacter();
    Point point = chara->getGridPosition();
    Direction dir = chara->getDirection();
    Location location{PlayerDataManager::getInstance()->getLocation().map_id, static_cast<int>(point.x), static_cast<int>(point.y), dir};
    PlayerDataManager::getInstance()->setLocation(location);
    
    // スクショをとって、ダンジョンメニューシーンをプッシュ
    string path = LastSupper::StringUtils::strReplace("global.json", "screen0.png", FileUtils::getInstance()->fullPathForFilename("save/global.json"));
    utils::captureScreen([=](bool success, string filename){
     if(success)
     {
         Sprite* screen = Sprite::create(filename);
         DungeonMenuScene* menu = DungeonMenuScene::create(screen->getTexture(), [=](){this->listener->setEnabled(true);});
         menu->onBackToTitleSelected = CC_CALLBACK_0(DungeonScene::onBackToTitleSelected, this);
         
         // メニューシーンをプッシュ
         Director::getInstance()->pushScene(menu);
         // cache削除
         Director::getInstance()->getTextureCache()->removeTextureForKey(filename);
     }
    }, path);
}

// メニューシーンでタイトルへ戻るを選択した時
void DungeonScene::onBackToTitleSelected()
{
    Director::getInstance()->popScene();
    DungeonSceneManager::destroy();
    Director::getInstance()->replaceScene(TitleScene::create());
}

// データクラスを取得
DungeonSceneData* DungeonScene::getData() const
{
    return dynamic_cast<DungeonSceneData*>(this->data);
}