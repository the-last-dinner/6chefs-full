//
//  EnemyTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/21.
//
//

#include "Tasks/EnemyTask.h"

// コンストラクタ
EnemyTask::EnemyTask() {FUNCLOG};

// デストラクタ
EnemyTask::~EnemyTask() {FUNCLOG};

// 初期化
bool EnemyTask::init()
{
    if(!GameTask::init()) return false;
    
    return true;
}