//
//  TIledMapData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#include "TIledMapData.h"

// tmxファイルのディレクトリ
const string TiledMapData::basePath = "map/";

// コンストラクタ
TiledMapData::TiledMapData(const string& mapFileName):
tiledMap(experimental::TMXTiledMap::create(basePath + mapFileName + ".tmx")),
mapObjs{nullptr}
{
	FUNCLOG
	this->setObjects();
}

// デストラクタ
TiledMapData::~TiledMapData()
{FUNCLOG}

// オブジェクトを格納
void TiledMapData::setObjects()
{
	FUNCLOG
	
	// オブジェクトの情報
	ValueMap objInfo;
	
	// オブジェクトの座標(左下)
	Point objPoint;
	
	// オブジェクトの大きさ
	Size objSize;
	
	// 共通部分の関数化
	// ValueMapを取得、座標、大きさを取得の処理
	function<void(cocos2d::Value)> func = [&](cocos2d::Value obj){objInfo = obj.asValueMap(); objPoint = Point(objInfo.at("x").asInt(), objInfo.at("y").asInt()); objSize = Size(objInfo.at("width").asInt(), objInfo.at("height").asInt());};
	
	//　当たり判定オブジェクトを取得
	ValueVector collisionObjs = this->tiledMap->getObjectGroup("collision")->getObjects();
	
	// マップオブジェクトを取得
	ValueVector mapObjs = this->tiledMap->getObjectGroup("event")->getObjects();
	
	// 当たり判定オブジェクト
	for(cocos2d::Value obj : collisionObjs)
	{
		func(obj);
		
		Point objGridPoint = MapUtils::convertToMapPoint(this->tiledMap->getContentSize(), objPoint) / GRID;
		MapObject* pObj = EventObject::create();
		pObj->setPosition(objPoint + objSize / 2);
		pObj->setObjectSize(objSize);
		pObj->setHit(true);
		pObj->setName("hit_" + to_string(static_cast<int>(objGridPoint.x)) + to_string(static_cast<int>(objGridPoint.y)));
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
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
		MapObject::TriggerType trigger = (objInfo.count("trigger") != 0)?static_cast<MapObject::TriggerType>(objInfo.at("trigger").asInt()):MapObject::TriggerType::NONE;
		
		if(objType == "")
		{
			pObj = EventObject::create();
			pObj->setEventId(eventId);
			pObj->setTrigger(trigger);
		}else if(objType == "chara" || objType == "main")
		{
			// オブジェクトのID取得
			int id = objInfo.at("objID").asInt();
			
			pObj = Character::create(id, static_cast<Character::Direction>(objInfo.at("direction").asInt()));
			pObj->setName(objType + ((objType == "main")? "" : "_" + to_string(id)));
			pObj->setHit(true);
		}
		
		pObj->setObjectSize(objSize);
		pObj->setPosition(objPoint + objSize / 2);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
	}
	return;
}

// TiledMapを取得
experimental::TMXTiledMap* TiledMapData::getTiledMap()
{return this->tiledMap;}

// 現在座標から、指定の方向に対して当たり判定があるか
bool TiledMapData::isHit(MapObject* obj, MapObject::Direction direction)
{	
	return false;
}