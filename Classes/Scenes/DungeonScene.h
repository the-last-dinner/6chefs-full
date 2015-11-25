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

class CameraTask;
class EnemyTask;
class EventTask;
class PlayerControlTask;

class LoadingLayer;
class Party;

class DungeonScene : public baseScene
{
// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(DungeonScene, DungeonSceneData*);
	
// インスタンス変数
private:
    EventListenerKeyboardLayer* listener { nullptr };
    cocos2d::FileUtils* fu { nullptr };
    TiledMapLayer* mapLayer { nullptr };
    AmbientLightLayer* ambientLightLayer {nullptr};
    
    CameraTask* cameraTask { nullptr };
    EnemyTask* enemyTask { nullptr };
    EventTask* eventTask { nullptr };
    PlayerControlTask* playerControlTask { nullptr };
    
    LoadingLayer* loadingLayer { nullptr };
    
    Party* party { nullptr };
    
// インスタンスメソッド
public:
    void onInitEventFinished();
    
private:
	DungeonScene();
	~DungeonScene();
	virtual bool init(DungeonSceneData* data);
	virtual void onPreloadFinished() override;
    
    Party* createParty();
    
    virtual void onMenuKeyPressed() override;
    DungeonSceneData* getData() const;
    
    void runEvent(const int eventId);
    
    friend class DungeonSceneManager;
};


#endif // __DUNGEON_SCENE_H__
