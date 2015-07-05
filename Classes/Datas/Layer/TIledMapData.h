//
//  TIledMapData.h
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#ifndef __TILED_MAP_DATA_H__
#define __TILED_MAP_DATA_H__

#include "Common.h"
#include "MapObjects/Objects.h"

class TiledMapData
{
	// クラス変数
private:
	static const string basePath;
	
	// インスタンスメソッド
public:
	TiledMapData(const string& mapFileName);
	~TiledMapData();
	experimental::TMXTiledMap* getTiledMap();
private:
	void setObjects();
	
	// インスタンス変数
public:
	vector<MapObject*> mapObjs;
private:
	experimental::TMXTiledMap* tiledMap;
	map<Point, bool> collisionObjs;
};

#endif //__TILED_MAP_DATA_H__

