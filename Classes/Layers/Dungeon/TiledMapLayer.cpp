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
    
    // イベントリスナを生成
    EventListenerKeyboardLayer* eventListener {EventListenerKeyboardLayer::create()};
    eventListener->onCursorKeyPressed = CC_CALLBACK_1(TiledMapLayer::onCursorKeyPressed, this);
    eventListener->pressingKey = CC_CALLBACK_1(TiledMapLayer::walking, this);
    this->addChild(eventListener);
    this->eventListener = eventListener;
	
	// TiledのマップをaddChild
    experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/" + CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::MAP, location.map_id)) };
    tiledMap->setPosition(Point::ZERO);
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
    
	// 主人公を配置
	Character* hero { Character::create(0, location.direction) };
	hero->setGridPosition(tiledMap->getContentSize(), Point(location.x, location.y));
	tiledMap->addChild(hero);
    this->hero = hero;
	
	// マップオブジェクトを配置
	this->setMapObjects();
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(AmbientLightLayer::NIGHT)};
    this->addChild(ambientLightLayer);
    this->ambientLightLayer = ambientLightLayer;
    
    hero->setLight(Light::create(Light::Information(20.f)), ambientLightLayer);

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
		
		Point objGridPoint = MapUtils::convertToMapPoint(this->tiledMap->getContentSize(), objPoint) / GRID;
		MapObject* pObj = EventObject::create();
		pObj->setPosition(objPoint);
		pObj->setContentSize(objSize);
		pObj->setHit(true);
		pObj->setName("hit_" + to_string(static_cast<int>(objGridPoint.x)) + to_string(static_cast<int>(objGridPoint.y)));
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
        pObj->drawDebugMask();
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
		}else if(objType == "chara" || objType == "main")
		{
			// オブジェクトのID取得
			int id = objInfo.at("objID").asInt();
			
			pObj = Character::create(id, static_cast<Direction>(objInfo.at("direction").asInt()));
			pObj->setName(objType + ((objType == "main")? "" : "_" + to_string(id)));
			pObj->setHit(true);
		}
		
		pObj->setContentSize(objSize);
		pObj->setPosition(objPoint);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
        pObj->drawDebugMask();
	}
}

// 指定座標のマップオブジェクトを取得(ない場合はnullptrを返す)
MapObject* TiledMapLayer::getMapObject(const Point& point)
{
	for(MapObject* obj : this->mapObjs)
	{
		Rect rect {obj->getBoundingBox() };
		if(rect.containsPoint(point)) return obj;
	}
	return nullptr;
}

// 座標から指定の方向に対して当たり判定があるか
bool TiledMapLayer::isHit(MapObject* obj, const Direction& direction)
{
	// 移動先の座標を取得
	Point point = obj->getPosition() + MapUtils::getGridVector(direction) * (obj->getContentSize().width / GRID - 0.5f);
	MapObject* pObj = this->getMapObject(point);
	if(!pObj) return false;
	return pObj->isHit();
}


// イベントIDを取得
int TiledMapLayer::getEventId(Point point)
{
	MapObject* pObj = this->getMapObject(point);
	if(!pObj) return -1;
	return pObj->getEventId();
}

// 方向キーが押された時
void TiledMapLayer::onCursorKeyPressed(const Key& key)
{
    this->hero->setDirection(MapUtils::keyToDirection(key));
}

void TiledMapLayer::walking(const Key& key)
{
    Direction direction {MapUtils::keyToDirection(key)};
    // 主人公が動いていない、向きがキーを押した時と同じ、その方向に当たり判定がなかったら
    if(!this->hero->isMoving() && this->hero->getDirection() == direction && !this->isHit(this->hero, direction))
    {
        Direction moveDirection = this->eventListener->getMoveDirection(this->hero->getMovingDirection(), key);
        Point movement = MapUtils::getGridVector(moveDirection) * 2;
        this->runAction(Sequence::create(Spawn::create(CallFunc::create([=](){this->hero->stamp();this->hero->setMovingDirection(moveDirection);}),
                                                       TargetedAction::create(this->tiledMap, MoveBy::create(Character::DURATION_FOR_ONE_STEP, - movement)),
                                                       TargetedAction::create(this->hero, MoveBy::create(Character::DURATION_FOR_ONE_STEP, movement)),
                                                       nullptr),
                                         CallFunc::create([=](){this->hero->setMovingDirection(Direction::NONE);}),
                                         nullptr));
    }
}