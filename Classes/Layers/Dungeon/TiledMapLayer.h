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

class TiledMapLayer : public Layer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(TiledMapLayer, PlayerDataManager::Location)
	
	// クラス変数
public:
	static const string HERO_OBJECT_NAME;
	
	// インスタンスメソッド
private:
	TiledMapLayer();
	~TiledMapLayer();
	bool init(const PlayerDataManager::Location&);
	void setMapObjects();
public:
	string getFileName();
	void controlMainCharacter(ActionKeyManager::Key key);
	MapObject* getMapObject(const Point& point);
	bool isHit(MapObject* obj, const Direction& direction);
	int getEventId(Point point);
	int search(MapObject* obj);
	
	// インスタンス変数
private:
	experimental::TMXTiledMap* tiledMap { nullptr };
	vector<MapObject*> mapObjs {};
	string fileName {""};
};

#endif // __TILED_MAP_LAYER_H__
