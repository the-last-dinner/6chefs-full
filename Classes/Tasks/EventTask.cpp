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
#include "Event/EventScriptValidator.h"

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
            CC_SAFE_RELEASE(this->eventQueue.front());
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

// キューに指定IDイベントを後ろから詰める
void EventTask::pushEventBack(int eventId)
{
    GameEvent* event {this->createEventById(eventId)};
    if(!event) return;
    DungeonSceneManager::getInstance()->setEventListenerPaused(true);
    this->eventQueue.push_back(event);
}

// キューに指定IDイベントを前から詰める
void EventTask::pushEventFront(int eventId)
{
    GameEvent* event {this->createEventById(eventId)};
    if(!event) return;
    DungeonSceneManager::getInstance()->setEventListenerPaused(true);
    this->eventQueue.push_front(event);
}

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
    this->runningEvent->run();
}

// IDからイベントを生成
GameEvent* EventTask::createEventById(int eventId)
{
    DungeonSceneManager* manager {DungeonSceneManager::getInstance()};
    
    GameEvent* event { manager->getEventFactory()->createGameEvent(manager->getEventScript()->getScriptJson(eventId))};
    
    CC_SAFE_RETAIN(event);
    
    return event;
}

// 現在実行中のイベントがあるか
bool EventTask::isEventRunning()
{
    return this->runningEvent;
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
    this->runningEvent->update(delta);
    
    // 実行中イベントが終了していたら解放
    if(this->runningEvent->isDone())
    {
        CC_SAFE_RELEASE(this->runningEvent);
        this->runningEvent = nullptr;
    }
        
    // キューが空になったらupdate停止
    if(this->eventQueue.empty() && !this->runningEvent)
    {
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
        DungeonSceneManager::getInstance()->setEventListenerPaused(false);
    }
    
    // イベントを実行
    this->run();
}
