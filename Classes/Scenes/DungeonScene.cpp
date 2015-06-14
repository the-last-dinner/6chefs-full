//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/14.
//
//

#include "DungeonScene.h"

// シーン生成
Scene* DungeonScene::createScene()
{
	Scene* scene = Scene::create();
	DungeonScene* layer = DungeonScene::create();
	scene->addChild(layer);
	return scene;
}

// コンストラクタ
DungeonScene::DungeonScene()
{FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{FUNCLOG}

// 初期化
bool DungeonScene::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	this->addChild(Sprite::createWithSpriteFrameName("title.png"));
	this->addChild(TiledMapManager::getInstance()->getTiledMap());
	
	return true;
}