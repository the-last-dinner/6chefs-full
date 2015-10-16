//
//  GameTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#ifndef __LastSupper__GameTask__
#define __LastSupper__GameTask__

#include "Common.h"

class TaskMediator;

// タスククラスの基底
class GameTask : public Ref
{
// インスタンス変数
protected:
    TaskMediator* mediator;
    
// インスタンスメソッド
protected:
    GameTask();
    ~GameTask();
    virtual bool init(TaskMediator* mediator);
};

#endif /* defined(__LastSupper__GameTask__) */
