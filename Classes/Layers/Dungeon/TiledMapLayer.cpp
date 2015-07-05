//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#include "TiledMapLayer.h"

// コンストラクタ
TiledMapLayer::TiledMapLayer():
data(nullptr)
{FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer()
{FUNCLOG}

// create関数
Layer* TiledMapLayer::create(const string& mapFileName)
{
	TiledMapLayer* pRet = new TiledMapLayer();
	if (pRet && pRet->init(mapFileName)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

// 初期化
bool TiledMapLayer::init(const string& mapFileName)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// データクラス初期化
	this->data = new TiledMapData(mapFileName);
	
	// TiledのマップをaddChild
	experimental::TMXTiledMap* map = this->data->getTiledMap();
	map->setOpacity(0);
	this->addChild(map);
	
	// カメラを主人公中心にセット
	Point center = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	map->setPosition(center - map->getChildByName<Character*>("main")->getPosition());
	
	return true;
}