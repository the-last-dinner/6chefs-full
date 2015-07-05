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
mapObjs{nullptr},
collisionObjs{}
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
	
	// 共通部分の関数化
	function<void()> func = [](){};
	
	//　当たり判定オブジェクトを取得
	ValueVector collisionObjs = this->tiledMap->getObjectGroup("collision")->getObjects();
	
	// マップオブジェクトを取得
	ValueVector mapObjs = this->tiledMap->getObjectGroup("event")->getObjects();
	
	this->tiledMap->getObjectGroups();
	
	for(cocos2d::Value obj : collisionObjs)
	{
		// オブジェクトの情報を取得
		ValueMap objInfo = obj.asValueMap();
		
		// オブジェクトの座標を取得
		Point gridPoint = MapUtils::convertToMapPoint(this->tiledMap->getContentSize(), Point(objInfo.at("x").asInt(), objInfo.at("y").asInt())) / GRID;
		
		// オブジェクトの大きさを取得
		Size objSize = Size(objInfo.at("width").asInt(), objInfo.at("height").asInt());
		
		// 当たり判定オブジェクトの場合はそれぞれを一マスずつ分割して格納
		if(objInfo.count("EventID") == 0)
		{
			Vec2 objGridSize = objSize / GRID;
			
			for(int i = 0; i < objGridSize.x; i++)
			{
				for(int j = 0; j < objGridSize.y; j++)
				{
					this->collisionObjs.insert({Point(gridPoint.x + i, gridPoint.y - j - 1), true});
				}
			}
			continue;
		}
	}
	
	// マップオブジェクトの場合
	for(cocos2d::Value obj : mapObjs)
	{
		// 入れ物を用意
		MapObject* pObj {nullptr};

		// オブジェクトの情報を取得
		ValueMap objInfo = obj.asValueMap();
		
		// オブジェクトの座標を取得
		Point point = Point(objInfo.at("x").asInt(), objInfo.at("y").asInt());
		
		// オブジェクトの大きさを取得
		Size objSize = Size(objInfo.at("width").asInt(), objInfo.at("height").asInt());
		
		// オブジェクトタイプを取得
		string objType = objInfo.at("type").asString();
		
		int eventId;
		MapObject::TriggerType trigger;
		
		if(objType != "main"){
			// EventID取得
			eventId = objInfo.at("EventID").asInt();
		
			// trigger取得
			trigger = static_cast<MapObject::TriggerType>(objInfo.at("trigger").asInt());
		}
		
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
		}
		
		pObj->setObjectSize(objSize);
		pObj->setPosition(point + objSize / 2);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
	}
	return;
}

// TiledMapを取得
experimental::TMXTiledMap* TiledMapData::getTiledMap()
{
	FUNCLOG
	return this->tiledMap;
}
