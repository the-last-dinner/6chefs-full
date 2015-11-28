//
//  DungeonSceneManager.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#include "Managers/DungeonSceneManager.h"

#include "Datas/Scene/DungeonSceneData.h"
#include "Datas/MapObject/EnemyData.h"

#include "Event/EventFactory.h"
#include "Event/EventScriptValidator.h"

#include "Layers/Dungeon/TiledMapLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Scenes/DungeonScene.h"

#include "Tasks/EnemyTask.h"
#include "Tasks/EventTask.h"
#include "Tasks/PlayerControlTask.h"

#include "Models/StopWatch.h"

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
};

// デストラクタ
DungeonSceneManager::~DungeonSceneManager()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->eventFactory);
    CC_SAFE_RELEASE_NULL(this->scriprtValidator);
};

#pragma mark -
#pragma mark Getter Methods

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
    return this->getScene()->party;
}

#pragma mark -
#pragma mark Scene

// フェードアウト
void DungeonSceneManager::fadeOut(const Color3B& color, const float duration, function<void()> callback)
{
    Sprite* cover { Sprite::create() };
    cover->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    cover->setColor(color);
    cover->setPosition(cover->getContentSize() / 2);
    this->getScene()->addChild(cover, Priority::SCREEN_COVER);
    this->cover = cover;
    
    cover->setOpacity(0.f);
    cover->runAction(Sequence::createWithTwoActions(FadeIn::create(duration), CallFunc::create(callback)));
}

// フェードイン
void DungeonSceneManager::fadeIn(const float duration, function<void()> callback)
{
    if(!this->cover)
    {
        callback();
        return;
    }
    
    Sprite* cover { this->cover };
    this->cover = nullptr;
    
    cover->runAction(Sequence::create(FadeOut::create(duration), CallFunc::create(callback), RemoveSelf::create(), nullptr));
}

#pragma mark -
#pragma mark TiledMapLayer

// マップの大きさを取得
Size DungeonSceneManager::getMapSize() const
{
    return this->getMapLayer()->getMapSize();
}

// マップオブジェクトをマップに追加
void DungeonSceneManager::addMapObject(MapObject* mapObject)
{
    this->getMapLayer()->addMapObject(mapObject);
}

// 敵をマップに配置
void DungeonSceneManager::addEnemy(Enemy* enemy)
{
    this->getMapLayer()->addEnemy(enemy);
}

#pragma mark -
#pragma mark Director

// マップ切り替え
void DungeonSceneManager::changeMap(const Location& location, const int initEventId)
{
    // 敵を止める
    this->getScene()->enemyTask->stop();
    
    // 敵情報を生成し直して格納
    vector<SummonData> summonDatas { this->getScene()->enemyTask->createDatas(this->getMapObjectList()->getEnemiesAll(), location, PlayerDataManager::getInstance()->getLocation()) };
    this->summonDatas.clear();
    this->summonDatas = summonDatas;
    
    // 主人公一行の位置を登録
    vector<CharacterData> members { this->getParty()->getMembersData() };
    int memberCount = members.size();
    for(int i=0; i < memberCount; i++)
    {
        members[i].location = location;
    }
    PlayerDataManager::getInstance()->setLocation(members);
    
    // 必要な情報を設定していく
    DungeonSceneData* data { DungeonSceneData::create(location) };
    data->setInitialEventId(initEventId);
    
    Director::getInstance()->replaceScene(DungeonScene::create(data));
}

#pragma mark -
#pragma mark EventListener

// 指定キーが押されているかチェック
bool DungeonSceneManager::isPressed(const Key& key)
{
    return this->getScene()->listener->isPressed(key);
}

// 入力されている方向キーを取得
vector<Key> DungeonSceneManager::getPressedCursorKeys() const
{
    return this->getScene()->listener->getPressedCursorKeys();
}

#pragma mark -
#pragma mark EnemyTask

// 敵の出現情報を取得
vector<SummonData> DungeonSceneManager::getSummonDatas() const
{
    return this->summonDatas;
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

// キューにイベントを後ろから詰める
void DungeonSceneManager::pushEventBack(GameEvent* event)
{
    this->getScene()->eventTask->pushEventBack(event);
}

// キューにイベントを前から詰める
void DungeonSceneManager::pushEventFront(GameEvent* event)
{
    this->getScene()->eventTask->pushEventFront(event);
}

// キューにあるイベントを実行
void DungeonSceneManager::runEventQueue()
{
    this->getScene()->eventTask->runEventQueue();
}

// キューにイベントがあるか
bool DungeonSceneManager::existsEvent() const
{
    return this->getScene()->eventTask->existsEvent();
}

// 実行しているイベントのIDを取得
int DungeonSceneManager::getRunningEventId() const
{
    return this->getScene()->eventTask->getRunningEventId();
}

// エンキュー中のイベントIDを取得
int DungeonSceneManager::getPushingEventid() const
{
    return this->getScene()->eventTask->getPushingEventId();
}

#pragma mark -
#pragma mark PlayerControlTask

void DungeonSceneManager::setPlayerControlEnable(bool enable)
{
    this->getScene()->playerControlTask->setControlEnable(enable, this->getScene()->party);
}

#pragma mark -
#pragma mark StopWatch

StopWatch* DungeonSceneManager::getStopWatch()
{
    if(!this->stopWatch)
    {
        this->stopWatch = StopWatch::create(0);
        CC_SAFE_RETAIN(this->stopWatch);
    }
    return this->stopWatch;
}

void DungeonSceneManager::releaseStopWatch()
{
    CC_SAFE_RELEASE_NULL(this->stopWatch);
}

void DungeonSceneManager::pauseStopWatch()
{
    if(this->stopWatch)
    {
        this->stopWatch->stopCountDown();
    }
}

void DungeonSceneManager::startStopWatch()
{
    if(this->stopWatch)
    {
        this->stopWatch->startCountDown();
    }
}