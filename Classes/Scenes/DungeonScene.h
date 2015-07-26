//
//  DungeonScene.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Common.h"
#include "baseScene.h"
#include "Datas/Scene/DungeonSceneData.h"
#include "Layers/Dungeon/TiledMapLayer.h"

class DungeonScene : public baseScene
{
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(DungeonScene);
	
	// インスタンスメソッド
public:
	DungeonScene();
	~DungeonScene();
private:
	virtual bool init();
	void loadFinished();
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener;
	TiledMapLayer* mapLayer;
};


#endif // __DUNGEON_SCENE_H__
