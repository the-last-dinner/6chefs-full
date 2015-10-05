//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
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
TiledMapLayer::~TiledMapLayer(){FUNCLOG}

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
    
    // ファクトリを生成
    MapObjectFactory* factory {MapObjectFactory::create()};
    CC_SAFE_RETAIN(factory);
    
    // 共通リスト生成
    MapObjectList* objectList {MapObjectList::create()};
    CC_SAFE_RETAIN(objectList);
    this->objectList = objectList;
    
	// 主人公を配置
	Character* mainCharacter { Character::create(0, location.direction) };
    mainCharacter->setGridPosition(tiledMap->getContentSize(), Point(location.x, location.y));
	tiledMap->addChild(mainCharacter);
    this->mainCharacter = mainCharacter;
    objectList->setMainCharacter(mainCharacter);
    mainCharacter->setMapObjectList(objectList);
    
    // レイヤ別に処理が分かれるので用意
    map<MapObjectFactory::Group, string> typeToString
    {
        {MapObjectFactory::Group::COLLISION, "collision"},
        {MapObjectFactory::Group::EVENT, "event"},
        {MapObjectFactory::Group::CHARACTER, "Chara(object)"},
    };
    
    // 生成して配置
    for(int i {0}; i < static_cast<int>(MapObjectFactory::Group::SIZE); i++)
    {
        MapObjectFactory::Group group {static_cast<MapObjectFactory::Group>(i)};
        ValueVector infos {this->tiledMap->getObjectGroup(typeToString.at(group))->getObjects()};
        
        for(cocos2d::Value info : infos)
        {
            MapObject* obj {factory->createMapObject(group, info.asValueMap())};
            this->tiledMap->addChild(obj);
            obj->setMapObjectList(objectList);
            obj->drawDebugMask();
            objectList->add(obj);
        }
    }
    
    this->setPosition(-mainCharacter->getPosition() + Director::getInstance()->getWinSize() / 2);

    CC_SAFE_RELEASE(factory);
    
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