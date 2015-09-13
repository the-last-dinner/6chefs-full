//
//  DungeonSceneData.h
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#ifndef __DUNGEON_SCENE_DATA_H__
#define __DUNGEON_SCENE_DATA_H__

#include "SceneData.h"

class DungeonSceneData : public SceneData
{
	// クラスメソッド
public:
	CREATE_FUNC(DungeonSceneData)
	
	// インスタンスメソッド
private:
	DungeonSceneData();
	~DungeonSceneData();
	bool init();
};

#endif // __DUNGEON_SCENE_DATA_H__
