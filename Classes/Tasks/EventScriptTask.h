//
//  EventScriptTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#ifndef __LastSupper__EventScriptTask__
#define __LastSupper__EventScriptTask__

#include "Tasks/GameTask.h"

class TaskMediator;

class GameEvent;

class EventScriptTask : public GameTask
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(EventScriptTask, TaskMediator*)

// インスタンス変数
private:
    queue<GameEvent*> eventQueue {};
    bool running {false};
    
// インスタンスメソッド
private:
	EventScriptTask();
	~EventScriptTask();
    virtual bool init(TaskMediator* mediator);
    void run();
    bool isEventRunning();
    void popEventQueue();
    
public:
	void runEventScript(int eventId);
    void update(float delta);
};

#endif /* defined(__LastSupper__EventScriptTask__) */
