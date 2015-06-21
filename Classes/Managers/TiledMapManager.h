//
//  TiledMapManager.h
//  LastSupper
//
//  Created by Kohei on 2015/06/13.
//
//

#ifndef __TILED_MAP_MANAGER_H__
#define __TILED_MAP_MANAGER_H__

#include "define.h"

class TiledMapManager
{
	// クラスメソッド
public:
	static TiledMapManager* getInstance();
	static void destory();
	
	// シングルトンであるためにprivateに
private:
	TiledMapManager();												// コンストラクタ
	TiledMapManager(const TiledMapManager& other);					// デストラクタ
	TiledMapManager& operator = (const TiledMapManager& other);		// 代入演算子
	
	// インスタンスメソッド
private:
	void setCollisionMap();
public:
	~TiledMapManager();
	void setBasePath(const string& basePath);
	void setTiledMapWithFileName(const string& fileName);
	experimental::TMXTiledMap* getTiledMap();
	void removeTiledMap();
	Point toCocosPoint(const Point& mapGridPoint);
	Point toMapPoint(const Point& cocosPoint);
	Point toGridPoint(const Point& mapPoint);
	bool isHit(const Point& mapGridPoint);
	
	// インスタンス変数
private:
	string basePath;
	experimental::TMXTiledMap* tiledMap;
	ValueVector collisionObjs;
	map<Point, bool> collisionMap;
};

#endif // __TILED_MAP_MANAGER_H__
