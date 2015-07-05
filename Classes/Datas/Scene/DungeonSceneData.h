//
//  DungeonSceneData.h
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#ifndef __DUNGEON_SCENE_DATA_H__
#define __DUNGEON_SCENE_DATA_H__

#include "Common.h"
#include "SceneData.h"
#include "MapObjects/Objects.h"

class DungeonSceneData : public SceneData
{
	// インスタンスメソッド
public:
	DungeonSceneData(string mapName);
	~DungeonSceneData();
private:
	void init();
	vector<string> getPreLoadList(string type);
	
	// インスタンス変数
private:
	string mapName;
	FileUtils* fu;
	rapidjson::Document json;
	
};

#endif // __DUNGEON_SCENE_DATA_H__
