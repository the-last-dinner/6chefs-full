//
//  TiledMapLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#ifndef __TILED_MAP_LAYER_H__
#define __TILED_MAP_LAYER_H__

#include "Layers/Shader/SpotLightShaderLayer.h"

class MapObject;
class EventListenerKeyboardLayer;
class Character;
class MapObjectList;

class TiledMapLayer : public Layer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(TiledMapLayer, const PlayerDataManager::Location&)
	
	// インスタンスメソッド
private:
	TiledMapLayer();
	~TiledMapLayer();
	bool init(const PlayerDataManager::Location&);
	
public:
    Character* getMainCharacter();
    experimental::TMXTiledMap* getTiledMap();
    MapObjectList* getMapObjectList() const;
    
    
	// インスタンス変数
private:
	experimental::TMXTiledMap* tiledMap { nullptr };    // マップ背景
    Character* mainCharacter { nullptr };                        // 主人公
    MapObjectList* objectList { nullptr };              // マップオブジェクトのリスト
};

#endif // __TILED_MAP_LAYER_H__
