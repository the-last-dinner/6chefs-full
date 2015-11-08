//
//  DungeonSceneManager.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#include "Managers/DungeonSceneManager.h"

#include "Datas/Scene/DungeonSceneData.h"

#include "Event/EventFactory.h"
#include "Event/EventScriptValidator.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Scenes/DungeonScene.h"

#include "Tasks/EventTask.h"

// 唯一のインスタンス
static DungeonSceneManager* _instance {nullptr};

// インスタンスを取得
DungeonSceneManager* DungeonSceneManager::getInstance()
{
    if(!_instance) _instance = new DungeonSceneManager();
    
    return _instance;
}

// インスタンスの破棄
void DungeonSceneManager::destroy()
{
    delete _instance;
}

// コンストラクタ
DungeonSceneManager::DungeonSceneManager()
{
    FUNCLOG

    // イベントファクトリを生成
    EventFactory* eventFactory {EventFactory::create()};
    CC_SAFE_RETAIN(eventFactory);
    this->eventFactory = eventFactory;
    
    // イベントバリデータを生成
    EventScriptValidator* scriptValidator {EventScriptValidator::create()};
    CC_SAFE_RETAIN(scriptValidator);
    this->scriprtValidator = scriptValidator;
    
    // パーティを生成
    Party* party { Party::create(Character::create(0, Direction::FRONT)) };
    CC_SAFE_RETAIN(party);
    this->party = party;
};

// デストラクタ
DungeonSceneManager::~DungeonSceneManager()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->eventFactory);
    CC_SAFE_RELEASE_NULL(this->scriprtValidator);
    CC_SAFE_RELEASE_NULL(this->party);
};

// シーンを取得
DungeonScene* DungeonSceneManager::getScene() const
{
    return dynamic_cast<DungeonScene*>(Director::getInstance()->getRunningScene());
}

// マップレイヤを取得
TiledMapLayer* DungeonSceneManager::getMapLayer() const
{
    return this->getScene()->mapLayer;
}

// オブジェクトリストを取得
MapObjectList* DungeonSceneManager::getMapObjectList() const
{
    return this->getMapLayer()->getMapObjectList();
}

// イベントファクトリを取得
EventFactory* DungeonSceneManager::getEventFactory() const
{
    return this->eventFactory;
}

// シーンのイベントリスナ取得
EventListenerKeyboardLayer* DungeonSceneManager::getSceneEventListener() const
{
    return this->getScene()->listener;
}

// イベントスクリプトを取得
EventScript* DungeonSceneManager::getEventScript() const
{
    return dynamic_cast<DungeonSceneData*>(this->getScene()->data)->getEventScript();
}

// スクリプトバリデータを取得
EventScriptValidator* DungeonSceneManager::getScriptValidator() const
{
    return this->scriprtValidator;
}

// パーティを取得
Party* DungeonSceneManager::getParty() const
{
    return this->party;
}

#pragma mark -
#pragma mark EventListener

// インターバルを設定
void DungeonSceneManager::setInputCheckInterval(const float interval)
{
    this->getScene()->listener->setInputCheckInterval(interval);
}

// コールバックを呼び出しの有無を設定
void DungeonSceneManager::setEventListenerPaused(const bool paused)
{
    this->getScene()->listener->setPaused(paused);
}

// 指定キーが押されているかチェック
bool DungeonSceneManager::isPressed(const Key& key)
{
    return this->getScene()->listener->isPressed(key);
}

#pragma mark -
#pragma mark EventTask

// イベントを実行
void DungeonSceneManager::runEvent(const int eventId)
{
    this->getScene()->eventTask->runEvent(eventId);
}

// キューにイベントを後ろから詰める
void DungeonSceneManager::pushEventBack(const int eventId)
{
    this->getScene()->eventTask->pushEventBack(eventId);
}

// キューにイベントを前から詰める
void DungeonSceneManager::pushEventFront(const int eventId)
{
    this->getScene()->eventTask->pushEventFront(eventId);
}

// キューにあるイベントを実行
void DungeonSceneManager::runEventQueue()
{
    this->getScene()->eventTask->runEventQueue();
}

// キューにイベントがあるか
bool DungeonSceneManager::existsEvent()
{
    return this->getScene()->eventTask->existsEvent();
}