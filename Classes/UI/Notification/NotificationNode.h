//
//  NotificationNode.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/05.
//
//

#ifndef NotificationNode_h
#define NotificationNode_h

#include "Common.h"

class NotificationNode : public Node
{
// 定数
public:
    using AnimationCallback = function<void(NotificationNode*)>;
// インスタンス変数
protected:
    NotificationNode();
    ~NotificationNode();
public:
    virtual bool init();
    virtual void notify(AnimationCallback callback) = 0;
    virtual void close(AnimationCallback callback) = 0;
    virtual float getShowingDuration() const = 0;
};

#endif /* NotificationNode_h */
