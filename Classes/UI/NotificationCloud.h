//
//  NotificationCloud.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#ifndef NotificationCloud_h
#define NotificationCloud_h

#include "define.h"

class NotificationCloud : public Node
{
// 定数
private:
    static const float MARGIN_V;
    static const float MARGIN_H;
    static const float ANIMATION_DURATION;
    static const float DURATION;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(NotificationCloud, const string&)
    
// インスタンスメソッド
private:
    NotificationCloud();
    ~NotificationCloud();
    bool init(const string& message);
    void onShowAnimationFinished(function<void()> callback);
    
public:
    void notify(function<void()> callback = nullptr);
};

#endif /* NotificationCloud_h */
