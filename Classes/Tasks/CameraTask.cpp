//
//  CameraTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/06.
//
//

#include "Tasks/CameraTask.h"

#include "MapObjects/MapObject.h"

#include "Tasks/TaskMediator.h"

#include "Tasks/FollowType/NeverFollow.h"
#include "Tasks/FollowType/HorizontalFollow.h"
#include "Tasks/FollowType/VerticalFollow.h"
#include "Tasks/FollowType/BothFollow.h"

// コンストラクタ
CameraTask::CameraTask() {FUNCLOG};

// デストラクタ
CameraTask::~CameraTask()
{
    FUNCLOG
    
    this->stopFollowing();

    CC_SAFE_RELEASE_NULL(this->follow);
    CC_SAFE_RELEASE_NULL(this->target);
};

// 初期化
bool CameraTask::init(TaskMediator* mediator)
{
    if(!GameTask::init(mediator)) return false;
    
    // マップの大きさから、縦方向、横方向のカメラ移動を許可するか判定
    Size winSize {Director::getInstance()->getWinSize()};
    Size mapSize {mediator->getMapSize()};
    
    // 外枠の大きさ
    Size margin {GRID * 4, GRID * 4};
    
    // マップの大きさ - 想定される外枠の大きさ がウィンドウの大きさよりも大きい時、それぞれの方向へスクロール可能とする
    bool horizontalFollow { mapSize.width - margin.width > winSize.width };
    bool verticalFollow { mapSize.height - margin.height > winSize.height };
    
    // 縦横どちらにもカメラ移動不可の場合
    if(!horizontalFollow && !verticalFollow)
    {
        this->follow = NeverFollow::create();
    }
    // 縦方向のみカメラ移動を許可されている場合
    else if (!horizontalFollow && verticalFollow)
    {
        this->follow = VerticalFollow::create();
    }
    // 横方向のみカメラ移動を許可されている場合
    else if (horizontalFollow && !verticalFollow)
    {
        this->follow = HorizontalFollow::create();
    }
    // 縦横どちらにもカメラ移動可能な時
    else if (horizontalFollow && verticalFollow)
    {
        this->follow = BothFollow::create();
    }
    CC_SAFE_RETAIN(this->follow);
    
    this->resumeFollowing();
    
    return true;
}

// 追いかけるオブジェクトを設定
void CameraTask::setTarget(MapObject* target)
{
    CC_SAFE_RELEASE(this->target);
    CC_SAFE_RETAIN(target);
    this->target = target;
}

// 自動追尾を停止
void CameraTask::stopFollowing()
{
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

// 自動追尾を再開
void CameraTask::resumeFollowing()
{
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

// updateメソッド
void CameraTask::update(float delta)
{
    if(!this->target || !this->mediator || !this->follow) return;
    
    this->mediator->setMapPosition(this->follow->getPosition(this->mediator->getMapSize(), this->target->getPosition()));
}