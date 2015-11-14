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

class MapObject;
class EventListenerKeyboardLayer;
class Character;
class MapObjectList;

class TiledMapLayer : public Layer
{
// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(TiledMapLayer, const PlayerDataManager::Location&)

// インスタンス変数
private:
    experimental::TMXTiledMap* tiledMap { nullptr };    // マップ背景
    MapObjectList* objectList { nullptr };              // マップオブジェクトのリスト
    
// インスタンスメソッド
private:
	TiledMapLayer();
	~TiledMapLayer();
	bool init(const PlayerDataManager::Location&);
	
public:
    experimental::TMXTiledMap* getTiledMap();
    MapObjectList* getMapObjectList() const;
    Size getMapSize() const;
    void hideLayer(const string& layerName);
    void addMapObject(MapObject* mapObject);
    void addMapObject(MapObject* mapObject, const Point& gridPoint);
    void removeMapObject(MapObject* mapObject);
    void setZOrderByPosition(MapObject* mapObject);
};

#endif // __TILED_MAP_LAYER_H__
