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
    if(!Layer::init()) return false;
    
	// Tiledのマップを生成
    experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/" + CsvDataManager::getInstance()->getMapFileName(location.map_id) + ".tmx") };
    tiledMap->setPosition(Point::ZERO);
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
    
    // オブジェクトリスト生成
    MapObjectList* objectList {MapObjectFactory::createMapObjectList(tiledMap)};
    CC_SAFE_RETAIN(objectList);
    this->objectList = objectList;
    
    // オブジェクトリストを元にマップ上に配置
    for(MapObject* mapObject : objectList->getMapObjects())
    {
        this->addMapObject(mapObject);
    }
    
	return true;
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

// マップの指定レイヤを隠す
void TiledMapLayer::hideLayer(const string& layerName)
{
    this->tiledMap->getLayer(layerName)->setVisible(false);
}

// マップにオブジェクトを追加
void TiledMapLayer::addMapObject(MapObject* mapObject)
{
    this->objectList->add(mapObject);
    mapObject->drawDebugMask();
    mapObject->setMapObjectList(this->objectList);
    this->tiledMap->addChild(mapObject);
    this->setZOrderByPosition(mapObject);
    mapObject->onMove = CC_CALLBACK_1(TiledMapLayer::setZOrderByPosition, this);
}

// マップにオブジェクトを追加
void TiledMapLayer::addMapObject(MapObject* mapObject, const Point& gridPoint)
{
    Point cocosPoint = MapUtils::convertToCCPoint(this->getMapSize(), gridPoint);
    mapObject->setPosition(cocosPoint.x + mapObject->getContentSize().width / 2, cocosPoint.y);
    mapObject->setGridPosition(gridPoint);
    this->addMapObject(mapObject);
}

// マス座標からZOrder値を設定
void TiledMapLayer::setZOrderByPosition(MapObject* mapObject)
{
    int z { static_cast<int>(mapObject->getGridPosition().y - this->tiledMap->getMapSize().height) - 1};
    mapObject->setLocalZOrder(z);
}