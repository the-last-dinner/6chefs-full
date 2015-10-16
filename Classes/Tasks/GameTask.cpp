//
//  GameTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#include "Tasks/GameTask.h"

// コンストラクタ
GameTask::GameTask() {FUNCLOG};

// デストラクタ
GameTask::~GameTask() {FUNCLOG};

// 初期化
bool GameTask::init(TaskMediator* mediator)
{
    if(!mediator) return false;
    
    this->mediator = mediator;
    
    return true;
}
