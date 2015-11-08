//
//  EventTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#ifndef __LastSupper__EventScriptTask__
#define __LastSupper__EventScriptTask__

#include "Tasks/GameTask.h"

class GameEvent;

class EventTask : public GameTask
{
// クラスメソッド
public:
    CREATE_FUNC(EventTask)

// インスタンス変数
private:
    deque<GameEvent*> eventQueue {};
    GameEvent* runningEvent { nullptr };
    
// インスタンスメソッド
private:
	EventTask();
	~EventTask();
    virtual bool init();
    void run();
    bool isEventRunning();
    GameEvent* createEventById(int eventId);
    
public:
    void runEventQueue();
	void runEvent(int eventId);
    void pushEventBack(int eventId);
    void pushEventFront(int eventId);
    void update(float delta);
    bool existsEvent();
};

#endif /* defined(__LastSupper__EventScriptTask__) */
