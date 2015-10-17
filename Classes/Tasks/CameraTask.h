//
//  CameraTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/06.
//
//

#ifndef __LastSupper__CameraTask__
#define __LastSupper__CameraTask__

#include "Tasks/GameTask.h"

class MapObject;
class FollowType;
class TaskMediator;

class CameraTask : public GameTask
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CameraTask, TaskMediator*)

// インスタンス変数
private:
    MapObject* target { nullptr };
    FollowType* follow { nullptr };
    
// インスタンスメソッド
private:
    CameraTask();
    ~CameraTask();
    bool init(TaskMediator* mediator);
public:
    void setTarget(MapObject* target);
    void stopFollowing();
    void resumeFollowing();
    void update(float delta);
};

#endif /* defined(__LastSupper__CameraTask__) */
