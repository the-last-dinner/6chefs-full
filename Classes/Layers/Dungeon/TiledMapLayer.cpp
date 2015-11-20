//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/28.
//
//

#include "Layers/Dungeon/TiledMapLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/Character.h"
#include "MapObjects/MapObjectFactory.h"
#include "MapObjects/MapObjectList.h"
#include "MapObjects/Party.h"

// コンストラクタ
TiledMapLayer::TiledMapLayer(){FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer(){FUNCLOG}

// 初期化
bool TiledMapLayer::init(const Location& location)
{
    if(!Layer::init()) return false;
    
	// Tiledのマップを生成
    experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/" + CsvDataManager::getInstance()->getMapFileName(location.map_id) + ".tmx") };
    tiledMap->setPosition(Point::ZERO);
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
    
    // オブジェクトリスト生成
    MapObjectList* objectList {MapObjectFactory::createMapObjectList(tiledMap)};
    this->addChild(objectList);
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
    if(experimental::TMXLayer* layer { this->tiledMap->getLayer(layerName) })
    {
        layer->setVisible(false);
    }
}

// マップの指定レイヤを揺らす
void TiledMapLayer::swingLayer(const string& layerName)
{
    if(experimental::TMXLayer* layer { this->tiledMap->getLayer(layerName) })
    {
        layer->runAction(RepeatForever::create(Sequence::create(MoveTo::create(0.2f, Point(layer->getPosition().x, layer->getPosition().y + GRID * 0.2f)), MoveTo::create(0.2f, Point(layer->getPosition().x, layer->getPosition().y - GRID * 0.2f)), nullptr)));
    }
}

// マップレイヤのアクションを全て停止
void TiledMapLayer::stopLayerActions()
{
    for(Node* layerNode : this->tiledMap->getChildren())
    {
        layerNode->stopAllActions();
    }
}

// パーティをマップ上に設置
void TiledMapLayer::setParty(Party* party)
{
    if(!party) return;
    
    for(Character* member : party->getMembers())
    {
        this->addMapObject(member, false);
    }
    
}

// 敵をマップに配置
void TiledMapLayer::addEnemy(Enemy* enemy)
{
    if(!enemy) return;
    
    enemy->onEnterMap(this->objectList->getParty()->getMainCharacter()->getGridPosition());
    this->objectList->addEnemy(enemy);
    this->addMapObject(enemy, false);
}

// マップにオブジェクトを追加
void TiledMapLayer::addMapObject(MapObject* mapObject, bool addingToList)
{
    if(!mapObject) return;
    
    Point cocosPoint {MapUtils::convertToCCPoint(this->getMapSize(), mapObject->getGridPosition(), mapObject->getContentSize())};
    mapObject->setPosition(cocosPoint);
    mapObject->drawDebugMask();
    mapObject->setMapObjectList(this->objectList);
    this->tiledMap->addChild(mapObject);
    this->setZOrderByPosition(mapObject);
    mapObject->onMove = CC_CALLBACK_1(TiledMapLayer::setZOrderByPosition, this);
    
    if(!addingToList) return;
    
    this->objectList->add(mapObject);
    mapObject->onEnterMap();
}

// マス座標からZOrder値を設定
void TiledMapLayer::setZOrderByPosition(MapObject* mapObject)
{
    int z { static_cast<int>(mapObject->getGridPosition().y - this->tiledMap->getMapSize().height) - 1};
    mapObject->setLocalZOrder(z);
}