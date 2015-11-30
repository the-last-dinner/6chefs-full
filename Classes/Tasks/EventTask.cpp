//
//  EventTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#include "Tasks/EventTask.h"

#include "Event/GameEvent.h"
#include "Event/EventFactory.h"

#include "Event/EventScript.h"
#include "Managers/DungeonSceneManager.h"

// コンストラクタ
EventTask::EventTask(){FUNCLOG}

// デストラクタ
EventTask::~EventTask()
{
    FUNCLOG
    
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    
    // イベントキューが空でなかったら全て削除
    if(!this->eventQueue.empty())
    {
        for(int i {0}; i < this->eventQueue.size(); i++)
        {
            CC_SAFE_RELEASE(this->getGameEvent(this->eventQueue.front()));
            this->eventQueue.pop_front();
        }
    }
}

// 初期化
bool EventTask::init()
{
    if(!GameTask::init()) return false;

	return true;
}

// イベントキューにあるイベントを実行開始
void EventTask::runEventQueue()
{
    if(!this->existsEvent()) return;
    this->resetPushingEventId();
    this->run();
    // update開始
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

// イベントをIDから実行
void EventTask::runEvent(int eventId)
{
    this->pushEventBack(eventId);
    
    // 実行
    this->runEventQueue();
}

// イベントをIDベクタから実行、ベクタを全て実行するとコールバック呼び出し
void EventTask::runEvent(vector<int> eventIds, function<void()> callback)
{
    // ベクタが空ならコールバック
    if(eventIds.empty())
    {
        if(callback) callback();
        
        return;
    }
    
    int pushedNum { 0 };
    int lastEventId { 0 };
    
    for(int eventId : eventIds)
    {
        if(this->pushEventBack(eventId))
        {
            pushedNum++;
            lastEventId = eventId;
        }
    }
    
    // 一つも生成されていなければその場でコールバック
    if(pushedNum == 0)
    {
        if(callback) callback();
        
        return;
    }
    
    // キューにあるイベントを先頭から実行
    this->runEventQueue();
    
    this->callbackInfo = CallbackWithId({lastEventId, callback});
}

// イベントを実行
void EventTask::runEvent(GameEvent* event, function<void()> callback)
{
    this->pushEventBack(event);
    
    this->callbackInfo = CallbackWithId({static_cast<int>(EventID::UNDIFINED), callback});
    
    this->runEventQueue();
}

// キューに指定IDイベントを後ろから詰める
bool EventTask::pushEventBack(int eventId)
{
    GameEvent* event {this->createEventById(eventId)};
    if(!event) return false;
    this->eventQueue.push_back({eventId, event});
    
    return true;
}

// キューに指定IDイベントを前から詰める
bool EventTask::pushEventFront(int eventId)
{
    GameEvent* event {this->createEventById(eventId)};
    if(!event) return false;
    this->eventQueue.push_front({eventId, event});
    
    return true;
}

// キューにイベントを後ろから詰める、EventIDはUNDIFINEDを使用
void EventTask::pushEventBack(GameEvent* event)
{
    if(!event) return;
    
    this->eventQueue.push_back({etoi(EventID::UNDIFINED), event});
}

// キューにイベントを前から詰める、EventIDは現在実行中のものを使用
void EventTask::pushEventFront(GameEvent* event)
{
    if(!event) return;
    
    this->eventQueue.push_front({this->getEventId(this->runningEvent), event});
}

// 現在実行中のイベントがあるか
bool EventTask::isEventRunning()
{
    if(this->getGameEvent(this->runningEvent)) return true;
    
    return this->existsEvent();
}

// キューにイベントが存在するか
bool EventTask::existsEvent()
{
    return !this->eventQueue.empty();
}

// update
void EventTask::update(float delta)
{
    // 実行中イベントを更新
    this->getGameEvent(this->runningEvent)->update(delta);
    
    // 実行中イベントが終了していたら解放
    if(this->getGameEvent(this->runningEvent)->isDone())
    {
        if(this->callbackInfo.second && this->callbackInfo.first == this->getEventId(this->runningEvent))
        {
            function<void()> cb { this->callbackInfo.second };
            this->callbackInfo = CallbackWithId({static_cast<int>(EventID::UNDIFINED), nullptr});
            cb();
        }
        CC_SAFE_RELEASE(this->getGameEvent(this->runningEvent));
        this->runningEvent = EventWithId({static_cast<int>(EventID::UNDIFINED), nullptr});
    }
        
    // キューが空になったらupdate停止
    if(this->eventQueue.empty() && !this->getGameEvent(this->runningEvent))
    {
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
 
        if(this->onAllEventFinished) this->onAllEventFinished();
    }
    
    // イベントを実行
    this->run();
}

// 実行中のイベントIDを取得
int EventTask::getRunningEventId() const
{
    return this->getEventId(this->runningEvent);
}

// キューにあるイベントを全て取得
deque<EventTask::EventWithId> EventTask::getEvents() const
{
    return this->eventQueue;
}

#pragma mark -
#pragma mark pushingEventId

int EventTask::getPushingEventId() const
{
    return this->pushingEventId;
}

void EventTask::setPushingEventId(const int event_id)
{
    this->pushingEventId = event_id;
}

void EventTask::resetPushingEventId()
{
    this->pushingEventId = etoi(EventID::UNDIFINED);
}

#pragma mark -
#pragma mark private

// キューにある先頭のイベントを実行
void EventTask::run()
{
    // 実行中のイベントがあればリターン
    if(this->isEventRunning()) return;
    
    // イベントキューが空ならリターン
    if(this->eventQueue.empty()) return;
    
    // なければ先頭を実行
    this->runningEvent = this->eventQueue.front();
    this->eventQueue.pop_front();
    this->getGameEvent(this->runningEvent)->run();
}

// IDからイベントを生成
GameEvent* EventTask::createEventById(int eventId)
{
    if(eventId == static_cast<int>(EventID::UNDIFINED) || PlayerDataManager::getInstance()->checkEventIsDone(DungeonSceneManager::getInstance()->getLocation().map_id, eventId)) return nullptr;
    
    this->setPushingEventId(eventId);
    
    DungeonSceneManager* manager {DungeonSceneManager::getInstance()};
    
    GameEvent* event { manager->getEventFactory()->createGameEvent(manager->getEventScript()->getScriptJson(eventId))};
    
    CC_SAFE_RETAIN(event);
    
    if(this->onRunEvent) this->onRunEvent();
    
    return event;
}

// イベントIDを取得
int EventTask::getEventId(const EventWithId& eventWithId) const
{
    return eventWithId.first;
}

// イベントポインタを取得
GameEvent* EventTask::getGameEvent(const EventWithId& eventWithId) const
{
    return eventWithId.second;
}