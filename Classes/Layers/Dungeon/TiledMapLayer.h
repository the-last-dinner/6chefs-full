//
//  TiledMapLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#ifndef __TILED_MAP_LAYER_H__
#define __TILED_MAP_LAYER_H__

#include "Common.h"
#include "Datas/Layer/TiledMapData.h"
#include "Layers/Dungeon/CharacterMessageLayer.h"
#include "Layers/Dungeon/StoryMessageLayer.h"
#include "Layers/Dungeon/SystemMessageLayer.h"

class TiledMapLayer : public Layer
{
	// クラスメソッド
public:
	static Layer* create(const string& mapFileName, EventListenerKeyboard* listener);
	
	// インスタンスメソッド
private:
	TiledMapLayer();
	~TiledMapLayer();
	bool init(const string& mapFileName, EventListenerKeyboard* lisener);
public:
	void controlMainCharacter(ActionKeyManager::Key key);
	
	// インスタンス変数
private:
	TiledMapData* data;
	EventListenerKeyboard* parentListener;	// DungeonSceneのイベントリスナー
};

#endif // __TILED_MAP_LAYER_H__
