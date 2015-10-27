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
class MapObjectList;
class TaskMediator;

class DungeonScene : public baseScene
{
// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(DungeonScene);
	
// インスタンス変数
private:
    cocos2d::FileUtils* fu;
    TiledMapLayer* mapLayer { nullptr };
    AmbientLightLayer* ambientLightLayer {nullptr};
    MapObjectList* objectList { nullptr };
    TaskMediator* mediator { nullptr };
    
// インスタンスメソッド
public:
    TiledMapLayer* getMapLayer() const;
    EventListenerKeyboardLayer* getListener() const;
    
private:
	DungeonScene();
	~DungeonScene();
	virtual bool init() override;
	virtual void onPreloadFinished() override;
    virtual void onMenuKeyPressed() override;
    
    friend class TaskMediator;
};


#endif // __DUNGEON_SCENE_H__
