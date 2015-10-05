//
//  CameraTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/06.
//
//

#include "Tasks/CameraTask.h"

// コンストラクタ
CameraTask::CameraTask() {FUNCLOG};

// デストラクタ
CameraTask::~CameraTask() {FUNCLOG};

// 初期化
bool CameraTask::init(DungeonScene* scene)
{
    this->scene = scene;
    
    return true;
}
