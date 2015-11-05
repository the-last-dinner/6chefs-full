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

class EventScript;

class DungeonSceneData : public SceneData
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(DungeonSceneData, const PlayerDataManager::Location&)
    
// インスタンス変数
private:
    EventScript* eventScript { nullptr };
	
// インスタンスメソッド
private:
	DungeonSceneData();
	~DungeonSceneData();
    bool init(const PlayerDataManager::Location& location);
public:
    EventScript* getEventScript() const;
};

#endif // __DUNGEON_SCENE_DATA_H__
