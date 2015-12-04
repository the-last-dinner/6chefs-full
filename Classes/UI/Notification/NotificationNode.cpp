//
//  NotificationNode.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/05.
//
//

#include "UI/Notification/NotificationNode.h"

// コンストラクタ
NotificationNode::NotificationNode() {};

// デストラクタ
NotificationNode::~NotificationNode() {};

// 初期化
bool NotificationNode::init()
{
    if(!Node::init()) return false;
    
    // カスケード
    this->setCascadeColorEnabled(true);
    this->setCascadeOpacityEnabled(true);
    
    return true;
}
