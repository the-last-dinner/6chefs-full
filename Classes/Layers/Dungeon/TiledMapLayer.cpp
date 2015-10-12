//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/28.
//
//

#include "Layers/Dungeon/TiledMapLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/MapObjectFactory.h"
#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"

// コンストラクタ
TiledMapLayer::TiledMapLayer(){FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer()
{
    FUNCLOG
    
    CC_SAFE_RELEASE_NULL(this->objectList);
}

// 初期化
bool TiledMapLayer::init(const PlayerDataManager::Location& location)
{
	FUNCLOG
    if(!Layer::init()) return false;
    
	// Tiledのマップを生成
    experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/" + CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::MAP, location.map_id) + ".tmx") };
    tiledMap->setPosition(Point::ZERO);
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
    
    // オブジェクトリスト生成
    MapObjectList* objectList {MapObjectFactory::createMapObjectList(tiledMap)};
    CC_SAFE_RETAIN(objectList);
    this->objectList = objectList;
    
    // オブジェクトリストを元にマップ上に配置
    for(MapObject* obj : objectList->getMapObjects())
    {
        obj->drawDebugMask();
        obj->setMapObjectList(objectList);
        tiledMap->addChild(obj);
    }
    
	// 主人公を配置
	Character* mainCharacter { Character::create(0, location.direction) };
    mainCharacter->setGridPosition(tiledMap->getContentSize(), Point(location.x, location.y));
	tiledMap->addChild(mainCharacter);
    this->mainCharacter = mainCharacter;
    objectList->setMainCharacter(mainCharacter);
    mainCharacter->setMapObjectList(objectList);
    
	return true;
}

//主人公のオブジェクトを取得
Character* TiledMapLayer::getMainCharacter()
{
    return this->mainCharacter;
}

// マップを取得
experimental::TMXTiledMap* TiledMapLayer::getTiledMap()
{
    return this->tiledMap;
}

// マップオブジェクトのリストを取得
MapObjectList* TiledMapLayer::getMapObjectList() const
{
    return this->objectList;
}

// マップのサイズを取得
Size TiledMapLayer::getMapSize() const
{
    return this->tiledMap->getContentSize();
}