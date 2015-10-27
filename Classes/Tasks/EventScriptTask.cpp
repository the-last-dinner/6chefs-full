//
//  EventScriptTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#include "Tasks/EventScriptTask.h"

#include "Tasks/TaskMediator.h"

#include "Event/GameEvent.h"
#include "Event/EventFactory.h"
#include "Event/EventScriptValidator.h"

// コンストラクタ
EventScriptTask::EventScriptTask(){FUNCLOG}

// デストラクタ
EventScriptTask::~EventScriptTask()
{
    FUNCLOG
    
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    
    // イベントキューが空でなかったら全て削除
    if(!this->eventQueue.empty())
    {
        for(int i {0}; i < this->eventQueue.size(); i++)
        {
            this->popEventQueue();
        }
    }
}

// 初期化
bool EventScriptTask::init(TaskMediator* mediator)
{
    if(!GameTask::init(mediator)) return false;  
    
    // イベントスクリプト用バリデータをセット
    EventScriptValidator* validator { EventScriptValidator::create(mediator) };
    EventScriptManager::getInstance()->setValidator(validator);

	return true;
}

// イベントスクリプトを実行
void EventScriptTask::runEventScript(int eventId)
{
    // イベントを生成し、キューにプッシュする
    // 同時実行のSpawnとして生成しておく
    EventScriptManager* manager {EventScriptManager::getInstance()};
    
    GameEvent* event { manager->getFactory()->createGameEvent(manager->getScript(eventId))};
    
    CC_SAFE_RETAIN(event);
    
    this->eventQueue.push(event);
    
    // 実行
    this->run();
    
    // update開始
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

// キューにある先頭のイベントを実行
void EventScriptTask::run()
{
    // 実行中のイベントがあればリターン
    if(this->isEventRunning()) return;
    
    // イベントキューが空ならリターン
    if(this->eventQueue.empty()) return;
    
    // なければ先頭を実行
    this->eventQueue.front()->run();
    this->running = true;
}

// 現在実行中のイベントがあるか
bool EventScriptTask::isEventRunning()
{
    // キューが空なら実行中でない
    if(this->eventQueue.empty()) return false;
    
    // 先頭のイベントが実行中か確認
    return !this->eventQueue.front()->isDone() && this->running;
}

// update
void EventScriptTask::update(float delta)
{
    // キューの先頭イベントが終了していたらポップ
    if(this->eventQueue.front()->isDone())
    {
        this->popEventQueue();
        this->running = false;
    }
        
    // キューが空になったらupdate停止
    if(this->eventQueue.empty())
    {
        Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    }
    
    // イベントを実行
    this->run();
}

// イベントキューをポップ
void EventScriptTask::popEventQueue()
{
    if(this->eventQueue.empty()) return;
    
    CC_SAFE_RELEASE(this->eventQueue.front());
    this->eventQueue.pop();
}