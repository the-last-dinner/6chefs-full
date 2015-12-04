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

class NotificationNode;

class NotificationManager
{
// クラスメソッド
public:
    static NotificationManager* getInstance();
    static void destroy();
    
// インスタンスメソッド
public:
    void notifyMapName(const int mapId);
    void onNotifyEnterAnimationFinished(NotificationNode* node);
    void onNotifyExitAnimationFinished(NotificationNode* node);
};

#endif /* NotificationManager_h */
