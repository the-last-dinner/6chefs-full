//
//  DungeonScene.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Scenes/baseScene.h"

class AmbientLightLayer;
class TiledMapLayer;
class DungeonSceneData;
class EventScript;

class CameraTask;
class EventTask;
class PlayerControlTask;

class DungeonScene : public baseScene
{
// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(DungeonScene, DungeonSceneData*);
	
// インスタンス変数
private:
    cocos2d::FileUtils* fu;
    TiledMapLayer* mapLayer { nullptr };
    AmbientLightLayer* ambientLightLayer {nullptr};
    
    CameraTask* cameraTask { nullptr };
    EventTask* eventTask { nullptr };
    PlayerControlTask* playerControlTask { nullptr };
    
// インスタンスメソッド
public:
    EventListenerKeyboardLayer* getListener() const;
    
private:
	DungeonScene();
	~DungeonScene();
	virtual bool init(DungeonSceneData* data);
	virtual void onPreloadFinished() override;
    virtual void onMenuKeyPressed() override;
    DungeonSceneData* getData() const;
    
    void runEvent(const int eventId);
    
    friend class DungeonSceneManager;
};


#endif // __DUNGEON_SCENE_H__
