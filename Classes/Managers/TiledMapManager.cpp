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
TiledMapManager* TiledMapManager::getinstance()
{
	if(!_instance) _instance = new TiledMapManager();
	return _instance;
}

// コンストラクタ
TiledMapManager::TiledMapManager()
{FUNCLOG}

// デストラクタ
TiledMapManager::~TiledMapManager()
{FUNCLOG}