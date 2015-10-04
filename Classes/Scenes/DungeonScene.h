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
class EventScriptTask;
class ControlMainCharacterTask;
class DungeonMainMenuLayer;

class DungeonScene : public baseScene
{
// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(DungeonScene);
	
// インスタンス変数
private:
    TiledMapLayer* mapLayer { nullptr };
    AmbientLightLayer* ambientLightLayer {nullptr};
    EventScriptTask* eventScriptTask { nullptr };
    ControlMainCharacterTask* controlMainCharacterTask {nullptr};
    DungeonMainMenuLayer* mainMenu { nullptr };
    
// インスタンスメソッド
public:
    void runEvent(int event_id);
    void onMenuHidden();
    
private:
	DungeonScene();
	~DungeonScene();
	virtual bool init() override;
	virtual void onPreloadFinished() override;
    virtual void onCursorKeyPressed(const Key& key) override;
    virtual void onSpaceKeyPressed() override;
    virtual void onMenuKeyPressed() override;
    virtual void intervalInputCheck(const vector<Key>& keys);
	
	friend class EventScriptTask;
    friend class ControlMainCharacterTask;
};


#endif // __DUNGEON_SCENE_H__
