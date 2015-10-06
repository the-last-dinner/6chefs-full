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
    
    this->scheduleUpdate();
    
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
    this->unscheduleUpdate();
}

// 自動追尾を再開
void CameraTask::resumeFollowing()
{
    this->scheduleUpdate();
}

// updateメソッド
void CameraTask::update(float delta)
{
    if(!this->target) return;
    
    this->scene->mapLayer->setPosition(-this->target->getPosition() + Director::getInstance()->getWinSize() / 2);
}