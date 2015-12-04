//
//  MapNameNotification.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#ifndef MapNameNotification_h
#define MapNameNotification_h

#include "UI/NotificationNode.h"

class MapNameNotification : public NotificationNode
{
// 定数
private:
    static const float MARGIN_V;
    static const float MARGIN_H;
    static const float ANIMATION_DURATION;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(MapNameNotification, const string&)
    
// インスタンスメソッド
private:
    MapNameNotification();
    ~MapNameNotification();
    bool init(const string& message);
    
public:
    virtual void notify(AnimationCallback callback);
    virtual void close(AnimationCallback callback);
    virtual float getShowingDuration() const;
};

#endif /* NotificationCloud_h */
