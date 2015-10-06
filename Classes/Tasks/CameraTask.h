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

class CameraTask : public Node
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CameraTask, DungeonScene*)

// インスタンス変数
    DungeonScene* scene {nullptr};
    MapObject* target { nullptr };
    
// インスタンスメソッド
private:
    CameraTask();
    ~CameraTask();
    virtual bool init(DungeonScene* scene) override;
    void update(float delta);
public:
    void setTarget(MapObject* target);
    void stopFollowing();
    void resumeFollowing();
};

#endif /* defined(__LastSupper__CameraTask__) */
