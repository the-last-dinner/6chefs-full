//
//  CameraTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/06.
//
//

#include "Tasks/CameraTask.h"

#include "MapObjects/MapObject.h"

#include "Scenes/DungeonScene.h"

#include "Layers/Dungeon/TiledMapLayer.h"

// コンストラクタ
CameraTask::CameraTask() {FUNCLOG};

// デストラクタ
CameraTask::~CameraTask() {FUNCLOG};

// 初期化
bool CameraTask::init(DungeonScene* scene)
{
    if(!Node::init()) return false;
    
    this->scene = scene;
    
        this->resumeFollowing();
    
    return true;
}

// 追いかけるオブジェクトを設定
void CameraTask::setTarget(MapObject* target)
{
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
    if(!this->target || this->target->getReferenceCount() == 0) return;
    
    this->scene->mapLayer->setPosition(-this->target->getPosition() + Director::getInstance()->getWinSize() / 2);
}