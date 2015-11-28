//
//  DungeonCameraScene.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#ifndef __LastSupper__DungeonCameraScene__
#define __LastSupper__DungeonCameraScene__

#include "Scenes/DungeonScene.h"

#include "Event/GameEvent.h"

class DungeonCameraScene : public DungeonScene
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_TWO_PARAM(DungeonCameraScene, DungeonSceneData*, Vector<GameEvent*>)
    
// インスタンスメソッド
private:
    DungeonCameraScene();
    ~DungeonCameraScene();
    bool init(DungeonSceneData* data, Vector<GameEvent*> events);
    virtual void onEnter();
    virtual void onPreloadFinished(LoadingLayer* loadingLayer);
    void onInitEventFinished(LoadingLayer* loadingLayer);
};

#endif /* defined(__LastSupper__DungeonCameraScene__) */
