//
//  NotificationManager.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/05.
//
//

#ifndef NotificationManager_h
#define NotificationManager_h

#include "define.h"

class NotificationManager
{
// クラスメソッド
public:
    static NotificationManager* getInstance();
    static void destroy();
};

#endif /* NotificationManager_h */
