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
class AmbientLightLayer;
class EventListenerKeyboardLayer;
class Character;

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
	void setMapObjects();
public:
	MapObject* getMapObject(const Point& point);
    MapObject* getMapObject(const Rect& rect);
    bool isHit(MapObject* obj, const Direction& direction);
	bool isHit(MapObject* obj, const Direction (&directions)[2]);
	int getEventId(Point point);
	int search(MapObject* obj);
    void walking(const Key& key);
    Character* getMainCharacter();
    experimental::TMXTiledMap* getTiledMap();
    
	// インスタンス変数
private:
	experimental::TMXTiledMap* tiledMap { nullptr };    // マップ背景
    AmbientLightLayer* ambientLightLayer { nullptr };   // 環境光レイヤー
	vector<MapObject*> mapObjs {};                      // マップオブジェクトのベクタ
    Character* mainCharacter { nullptr };                        // 主人公
};

#endif // __TILED_MAP_LAYER_H__
