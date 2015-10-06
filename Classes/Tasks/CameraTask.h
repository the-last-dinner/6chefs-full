//
//  CameraTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/06.
//
//

#ifndef __LastSupper__CameraTask__
#define __LastSupper__CameraTask__

#include "Common.h"

class DungeonScene;
class MapObject;
class FollowType;

class CameraTask : public Node
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CameraTask, DungeonScene*)

// インスタンス変数
private:
    DungeonScene* scene {nullptr};
    MapObject* target { nullptr };
    FollowType* follow { nullptr };
    
// インスタンスメソッド
private:
    CameraTask();
    ~CameraTask();
    bool init(DungeonScene* scene);
public:
    void setTarget(MapObject* target);
    void stopFollowing();
    void resumeFollowing();
    void update(float delta);
};

#endif /* defined(__LastSupper__CameraTask__) */
