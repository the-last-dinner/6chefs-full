//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#include "Layers/Dungeon/TiledMapLayer.h"

#include "Effects/AmbientLightLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/Objects.h"

// コンストラクタ
TiledMapLayer::TiledMapLayer(){FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer(){FUNCLOG}

// 初期化
bool TiledMapLayer::init(const PlayerDataManager::Location& location)
{
	FUNCLOG
    if(!Layer::init()) return false;
    
	// TiledのマップをaddChild
    experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/" + CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::MAP, location.map_id) + ".tmx") };
    tiledMap->setPosition(Point::ZERO);
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
    
	// 主人公を配置
	Character* mainCharacter { Character::create(0, location.direction) };
    mainCharacter->setGridPosition(tiledMap->getContentSize(), Point(location.x, location.y));
	tiledMap->addChild(mainCharacter);
    this->mainCharacter = mainCharacter;
	
	// マップオブジェクトを配置
	this->setMapObjects();
    
    //環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    mainCharacter->setLight(Light::create(Light::Information(20.f)), ambientLightLayer);
    
    tiledMap->setPosition(-mainCharacter->getPosition() + Director::getInstance()->getWinSize() / 2);

	return true;
}

// マップオブジェクトを配置
void TiledMapLayer::setMapObjects()
{
	// オブジェクトの情報
	ValueMap objInfo;
	
	// オブジェクトの座標(左下)
	Point objPoint;
	
	// オブジェクトの大きさ
	Size objSize;
	
	// 共通部分の関数化
	// ValueMapを取得、座標、大きさを取得の処理
	function<void(cocos2d::Value)> func
	{
		[&](cocos2d::Value obj)
		{
			objInfo = obj.asValueMap();
			objPoint = Point(objInfo.at("x").asInt(), objInfo.at("y").asInt());
			objSize = Size(objInfo.at("width").asInt(), objInfo.at("height").asInt());
		}
	};
	
	//　当たり判定オブジェクトを取得
	ValueVector collisionObjs = this->tiledMap->getObjectGroup("collision")->getObjects();
	
	// マップオブジェクトを取得
	ValueVector mapObjs = this->tiledMap->getObjectGroup("event")->getObjects();
	
	// 当たり判定オブジェクト
	for(cocos2d::Value obj : collisionObjs)
	{
		func(obj);
		
		MapObject* pObj = EventObject::create();
		pObj->setPosition(objPoint + objSize / 2);
		pObj->setContentSize(objSize);
		pObj->setHit(true);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
        pObj->drawDebugMask();
        pObj->setCollisionRect(Rect(0, 0, objSize.width, objSize.height));
	}
	
	// マップオブジェクト
	for(cocos2d::Value obj : mapObjs)
	{
		func(obj);
		
		// 入れ物を用意
		MapObject* pObj {nullptr};
		
		// オブジェクトタイプを取得
		string objType = objInfo.at("type").asString();
		
		// EventID取得
		int eventId = (objInfo.count("EventID") != 0)?objInfo.at("EventID").asInt():-1;
		
		// trigger取得
		Trigger trigger = (objInfo.count("trigger") != 0)?static_cast<Trigger>(objInfo.at("trigger").asInt()):Trigger::SIZE;
		
		if(objType == "")
		{
			pObj = EventObject::create();
			pObj->setEventId(eventId);
			pObj->setTrigger(trigger);
		}else if(objType == "chara")
		{
			// オブジェクトのID取得
			int id = objInfo.at("objID").asInt();
			
			pObj = Character::create(id, static_cast<Direction>(objInfo.at("direction").asInt()));
			pObj->setHit(true);
		}
		
		pObj->setContentSize(objSize);
		pObj->setPosition(objPoint + objSize / 2);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
        pObj->drawDebugMask();
        pObj->setCollisionRect(Rect(0, 0, objSize.width, objSize.height));
	}
}

// 指定座標のマップオブジェクトを取得(ない場合はnullptrを返す)
MapObject* TiledMapLayer::getMapObject(const Point& point)
{
	for(MapObject* obj : this->mapObjs)
	{
		Rect rect { obj->getCollisionRect() };
		if(rect.containsPoint(point))
            return obj;
	}
	return nullptr;
}

// 指定範囲内のマップオブジェクトを取得
MapObject* TiledMapLayer::getMapObject(const Rect& rect)
{
    for(MapObject* obj : this->mapObjs)
    {
        Point point {obj->getPosition()};
        if(rect.containsPoint(point)) return obj;
    }
    return nullptr;
}

// 座標から指定の方向に対して当たり判定があるか
bool TiledMapLayer::isHit(MapObject* obj, const Direction& direction)
{
    // 移動先の座標を取得
    Point point { obj->getAdjacentPosition(direction)};
    MapObject* pObj {this->getMapObject(point)};
    if(!pObj) return false;
    return pObj->isHit();
}

// 座標から指定の方向に対して当たり判定があるか
bool TiledMapLayer::isHit(MapObject* obj, const Direction (&directions)[2])
{
	// 移動先の座標を取得
    Point point { obj->getAdjacentPosition(directions)};
    MapObject* pObj {this->getMapObject(point)};
	if(!pObj) return false;
	return pObj->isHit();
}


// イベントIDを取得
int TiledMapLayer::getEventId(Point point)
{
	MapObject* pObj = this->getMapObject(point);
    if(!pObj) return MapObject::EventID::UNDIFINED;
	return pObj->getEventId();
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