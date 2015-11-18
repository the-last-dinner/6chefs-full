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
// 定数
public:
    using CoverInfo = pair<bool, Color3B>;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(DungeonSceneData, const Location&)
    
// インスタンス変数
private:
    Location initialLocation {};
    EventScript* eventScript { nullptr };
    CoverInfo coverInfo { CoverInfo({false, Color3B::BLACK}) };
	
// インスタンスメソッド
private:
	DungeonSceneData();
	~DungeonSceneData();
    bool init(const Location& location);
public:
    Location getInitialLocation() const;
    EventScript* getEventScript() const;
    
    
    // フェードアウト用カバー
    void setCoverInfo(const CoverInfo& coverInfo);
    bool remainsCover() const;
    Color3B getCoverColor() const;
};

#endif // __DUNGEON_SCENE_DATA_H__
