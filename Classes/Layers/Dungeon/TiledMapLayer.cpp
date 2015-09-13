//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#include "Layers/Dungeon/TiledMapLayer.h"

#include "MapObjects/Objects.h"

#include "Effects/Light.h"
#include "Effects/ShadowLayer.h"

// クラス変数初期化
const string TiledMapLayer::HERO_OBJECT_NAME = "hero";

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
	experimental::TMXTiledMap* tiledMap { experimental::TMXTiledMap::create("map/MAIN-Syokudou1.tmx") };
	tiledMap->setZOrder(static_cast<int>(Priority::MAP));
	this->addChild(tiledMap);
	this->tiledMap = tiledMap;
	
	ShadowLayer* shadow {ShadowLayer::create(Color4B(0,0,0,200))};
	shadow->setGlobalZOrder(static_cast<int>(Priority::SHADOW));
	this->addChild(shadow);
	
	// 主人公を配置
	Character* hero { Character::create(0, Direction::FRONT) };
	hero->setGridPosition(tiledMap->getContentSize(), Point(location.x, location.y));
	hero->setName(HERO_OBJECT_NAME);
	tiledMap->addChild(hero);
	
	this->runAction(Sequence::createWithTwoActions(DelayTime::create(3), CallFunc::create([hero](){hero->setLight(Light::create(200));})));
	
	// マップオブジェクトを配置
	this->setMapObjects();
	
	// カメラを主人公中心にセット
	Point center = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	//map->setPosition(center - map->getChildByName<Character*>("main")->getPosition());

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
		TriggerType trigger = (objInfo.count("trigger") != 0)?static_cast<TriggerType>(objInfo.at("trigger").asInt()):TriggerType::NONE;
		
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
		
		pObj->setObjectSize(objSize);
		pObj->setPosition(objPoint + objSize / 2);
		this->tiledMap->addChild(pObj);
		this->mapObjs.push_back(pObj);
	}
}

// 指定座標のマップオブジェクトを取得(ない場合はnullptrを返す)
MapObject* TiledMapLayer::getMapObject(const Point& point)
{
	for(MapObject* obj : this->mapObjs)
	{
		Rect rect {obj->getBoundingBox() };
		if(rect.containsPoint(point) && obj->getName() != "hero") return obj;
	}
	return nullptr;
}

// 座標から指定の方向に対して当たり判定があるか
bool TiledMapLayer::isHit(MapObject* obj, const Direction& direction)
{
	// 移動先の座標を取得
	Point point = obj->getPosition() + movementMap.at(direction) * (obj->getObjectSize().width / GRID - 0.5f);
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

// マップファイル名を取得
string TiledMapLayer::getFileName()
{
	return this->fileName;
}

// 主人公の操作
void TiledMapLayer::controlMainCharacter(ActionKeyManager::Key key)
{
	FUNCLOG
	switch(key)
	{
		case::ActionKeyManager::Key::DOWN:
		case::ActionKeyManager::Key::LEFT:
		case::ActionKeyManager::Key::RIGHT:
		case::ActionKeyManager::Key::UP:
		{
			ActionKeyManager* manager = ActionKeyManager::getInstance();
			experimental::TMXTiledMap* map = this->tiledMap;
			Character* main = map->getChildByName<Character*>(HERO_OBJECT_NAME);
			
				
			// 移動キーが押された時は、向きを変える
			Direction direction = static_cast<Direction>(key);
			main->setDirection(direction);
			
			// 動いてる向きを取得
			Direction movingDirection = main->getMovingDirection();
			// ループを解除
			this->unschedule("ControlCheck");
			
			// ループを開始
			this->schedule([=](float delta){
				if(ActionKeyManager::getInstance()->isPressed(key))
				{
					// 主人公が動いていない、向きがキーを押した時と同じ、その方向に当たり判定がなかったら
					if(!main->isMoving() && main->getDirection() == direction && !this->isHit(main, direction))
					{
						Direction moveDirection = manager->getMoveDirection(movingDirection, key);
						Point movement = movementMap.at(moveDirection);
						this->runAction(Sequence::create(Spawn::create(CallFunc::create([=](){main->stamp();main->setMovingDirection(moveDirection);}),
																	   TargetedAction::create(map, MoveBy::create(Character::SECOND_PER_GRID, - movement)),
																	   TargetedAction::create(main, MoveBy::create(Character::SECOND_PER_GRID, movement)),
																	   nullptr),
														 CallFunc::create([=](){main->setMovingDirection(Direction::NONE);}),
														 nullptr));
					}
				}
				else
				{
					// キーを離したらループを解除
					this->unschedule("ControlCheck");
				}
					
			}, ActionKeyManager::INPUT_CHECK_SPAN, "ControlCheck");
			
			break;
		}
		case::ActionKeyManager::Key::SPACE:
			break;
		default:
			break;
	}

}