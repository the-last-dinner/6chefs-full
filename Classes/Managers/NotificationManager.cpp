//
//  NotificationManager.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/05.
//
//

#include "Managers/NotificationManager.h"

// 唯一のインスタンス
static NotificationManager* _instance {nullptr};

// インスタンスを取得
NotificationManager* NotificationManager::getInstance()
{
    if(!_instance) _instance = new NotificationManager();
    
    return _instance;
}

// インスタンスの破棄
void NotificationManager::destroy()
{
    delete _instance;
}
