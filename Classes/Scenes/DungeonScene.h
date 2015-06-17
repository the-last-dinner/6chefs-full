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
#include "MapObjects/Objects.h"

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
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener;
};


#endif // __DUNGEON_SCENE_H__
