//
//  TiledMapManager.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/13.
//
//

#include "TiledMapManager.h"

// 唯一のインスタンスを初期化
static TiledMapManager* _instance = nullptr;

// 唯一のインスタンスを取得
TiledMapManager* TiledMapManager::getInstance()
{
	if(!_instance) _instance = new TiledMapManager();
	return _instance;
}

// インスタンスを破棄
void TiledMapManager::destory()
{
	delete _instance;
	return;
}

// コンストラクタ
TiledMapManager::TiledMapManager():
basePath(""),
tiledMap(nullptr),
collisionMap(),
eventMap()
{FUNCLOG}

// デストラクタ
TiledMapManager::~TiledMapManager()
{FUNCLOG}

// マップファイルが存在するディレクトリのパスを設定
void TiledMapManager::setBasePath(const string& basePath)
{
	FUNCLOG
	this->basePath = basePath;
	return;
}

// マップデータを読み込み
void TiledMapManager::setTiledMapWithFileName(const string& fileName)
{
	FUNCLOG
	this->tiledMap = experimental::TMXTiledMap::create(this->basePath + fileName + ".tmx");
	
	// どこにもaddchildしていない状態なので参照カウンタを+1しておく
	this->tiledMap->retain();
	
	// 当たり判定オブジェクトをmapに格納
	this->setCollisionMap();
	
	// イベントオブジェクトをmapに格納
	this->setEventMap();
	
	return;
}

// 当たり判定オブジェクトをmapに整形して格納
void TiledMapManager::setCollisionMap()
{
	FUNCLOG
	//　当たり判定のオブジェクトを取得
	ValueVector collisionObjs = this->tiledMap->getObjectGroup("collision")->getObjects();
	
	for(cocos2d::Value collisionObj : collisionObjs)
	{
		// 当たり判定オブジェクトの情報を取得
		ValueMap objInfo = collisionObj.asValueMap();
		
		// 当たり判定オブジェクトの座標を取得
		Point gridPoint = this->toGridPoint(this->toMapPoint(Point(objInfo.at("x").asInt(), objInfo.at("y").asInt())));
		
		// 当たり判定オブジェクトの大きさを取得
		Vec2 objGridSize = this->toGridPoint(Point(objInfo.at("width").asInt(), objInfo.at("height").asInt()));
		
		// 当たり判定オブジェクトの高さを元に、当たり判定オブジェクトの座標を左上にする(デフォルトで左下の座標になっている)
		gridPoint.y = gridPoint.y - objGridSize.y;
		
		// マップ全体のマス数を取得
		Vec2 mapGridSize = this->toGridPoint(this->tiledMap->getContentSize());
		
		// それぞれを一マスずつ分割して格納
		for(int i = 0; i < objGridSize.x; i++)
		{
			for(int j = 0; j < objGridSize.y; j++)
			{
				collisionMap.insert({Point(gridPoint.x + i, gridPoint.y + j), true});
			}
		}
	}
	return;
}

// イベントオブジェクトをmapに格納
void TiledMapManager::setEventMap()
{
	FUNCLOG
	//　イベントオブジェクトを取得
	ValueVector eventObjs = this->tiledMap->getObjectGroup("event")->getObjects();
	
	for(cocos2d::Value eventObj : eventObjs)
	{
		// オブジェクトの情報を取得
		ValueMap objInfo = eventObj.asValueMap();
		
		// オブジェクトの座標を取得
		Point gridPoint = this->toGridPoint(this->toMapPoint(Point(objInfo.at("x").asInt(), objInfo.at("y").asInt())));
		
		// オブジェクトの大きさを取得
		Vec2 objGridSize = this->toGridPoint(Point(objInfo.at("width").asInt(), objInfo.at("height").asInt()));
		
		// オブジェクトの高さを元に、当たり判定オブジェクトの座標を左上にする(デフォルトで左下の座標になっている)
		gridPoint.y = gridPoint.y - objGridSize.y;
		
		// マップ全体のマス数を取得
		Vec2 mapGridSize = this->toGridPoint(this->tiledMap->getContentSize());
		
		// それぞれを一マスずつ分割して格納
		for(int i = 0; i < objGridSize.x; i++)
		{
			for(int j = 0; j < objGridSize.y; j++)
			{
				eventMap.insert({Point(gridPoint.x + i, gridPoint.y + j), Point(objInfo.at("EventID").asInt(), objInfo.at("trigger").asInt())});
			}
		}
	}
	return;
}

// マップデータを取得
experimental::TMXTiledMap* TiledMapManager::getTiledMap()
{
	FUNCLOG
	return this->tiledMap;
}

// マップデータを破棄
void TiledMapManager::removeTiledMap()
{
	FUNCLOG
	this->tiledMap->release();
	return;
}

// マップ上のマス座標をcocos2d上の座標に変換
Point TiledMapManager::toCocosPoint(const Point& mapGridPoint)
{
	FUNCLOG
	return Point(mapGridPoint.x * GRID, this->tiledMap->getContentSize().height - mapGridPoint.y * GRID);
}

// cocos2d上の座標をマップ上座標に変換
Point TiledMapManager::toMapPoint(const Point& cocosPoint)
{
	FUNCLOG
	return Point(cocosPoint.x, (this->tiledMap->getContentSize().height - cocosPoint.y));
}

// Map上のピクセル座標をMap上のマス座標に変換
Point TiledMapManager::toGridPoint(const Point& mapPoint)
{
	FUNCLOG
	return mapPoint / GRID;
}

// 指定のマス座標に当たり判定があるかどうか判定
bool TiledMapManager::isHit(const Point& mapGridPoint)
{
	FUNCLOG
	// 与えられたキー（座標）が存在するか確認し、なければfalse、あればValueを返す
	return (collisionMap.count(mapGridPoint) == 0)?false:collisionMap.at(mapGridPoint);
}

// 指定のマスのイベントオブジェクトのIDを返す（なければ -1 を返す）
int TiledMapManager::getEventID(const Point& mapGridPoint)
{
	FUNCLOG
	return (eventMap.count(mapGridPoint) == 0)?-1:eventMap.at(mapGridPoint).y;
}