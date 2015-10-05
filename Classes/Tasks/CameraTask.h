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

class CameraTask : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CameraTask, DungeonScene*)

// インスタンス変数
    DungeonScene* scene {nullptr};
    
// インスタンスメソッド
private:
    CameraTask();
    ~CameraTask();
    bool init(DungeonScene* scene);
};

#endif /* defined(__LastSupper__CameraTask__) */
