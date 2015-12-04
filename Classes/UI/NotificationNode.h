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
// インスタンス変数
protected:
    NotificationNode();
    ~NotificationNode();
public:
    virtual bool init();
    virtual void notify(function<void(NotificationNode*)> callback) = 0;
    virtual void close() = 0;
    virtual float getShowingDuration() = 0;
};

#endif /* NotificationNode_h */
