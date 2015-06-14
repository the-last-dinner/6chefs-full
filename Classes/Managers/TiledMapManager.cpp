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

// コンストラクタ
TiledMapManager::TiledMapManager():
basePath(),
tiledMap(nullptr)
{FUNCLOG}

// デストラクタ
TiledMapManager::~TiledMapManager()
{FUNCLOG}

// マップファイルが存在するディレクトリのパスを設定
void TiledMapManager::setBasePath(string basePath)
{
	FUNCLOG
	this->basePath = basePath;
	return;
}

// マップデータを読み込み
void TiledMapManager::setTiledMapWithFileName(string fileName)
{
	FUNCLOG
	this->tiledMap = TMXTiledMap::create(this->basePath + fileName + ".tmx");
	return;
}

// マップデータを取得
TMXTiledMap* TiledMapManager::getTiledMap()
{
	FUNCLOG
	return this->tiledMap;
}