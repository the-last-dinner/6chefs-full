//
//  DungeonScene.h
//  LastSupper
//
//  Created by Kohei on 2015/06/14.
//
//

#ifndef __DUNGEON_SCENE_H__
#define __DUNGEON_SCENE_H__

#include "Common.h"
#include "baseScene.h"

class DungeonScene : public baseScene
{
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(DungeonScene);
	
	// インスタンスメソッド
private:
	virtual bool init();
public:
	DungeonScene();
	~DungeonScene();
};


#endif // __DUNGEON_SCENE_H__
