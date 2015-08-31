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
	CREATE_FUNC_WITH_PARAM(DungeonSceneData, string)
	
	// インスタンスメソッド
private:
	DungeonSceneData();
	~DungeonSceneData();
	bool init(const string&);
	vector<string> getPreLoadList(const string& type);
	
	// インスタンス変数
private:
	string mapName {""};
	FileUtils* fu { nullptr };
	rapidjson::Document json {};
	
};

#endif // __DUNGEON_SCENE_DATA_H__
