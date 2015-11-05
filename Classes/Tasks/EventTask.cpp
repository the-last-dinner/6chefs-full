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

// イベントスクリプトを実行
void EventTask::runEvent(int eventId)
{
    // イベントを生成し、キューにプッシュする
    // 同時実行のSpawnとして生成しておく
    DungeonSceneManager* manager {DungeonSceneManager::getInstance()};
    
    GameEvent* event { manager->getEventFactory()->createGameEvent(manager->getEventScript()->getScriptJson(eventId))};
    
    CC_SAFE_RETAIN(event);
    
    this->eventQueue.push_back(event);
    
    // 実行
    this->run();
    
    // update開始
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
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

// 現在実行中のイベントがあるか
bool EventTask::isEventRunning()
{
    return this->runningEvent;
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
    if(this->eventQueue.empty())
    {
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    }
    
    // イベントを実行
    this->run();
}
