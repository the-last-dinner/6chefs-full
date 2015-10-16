//
//  MapObjectFactory.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#include "MapObjects/MapObjectFactory.h"

#include "MapObjects/MapObjectList.h"

#include "Objects.h"

// コンストラクタ
MapObjectFactory::MapObjectFactory() {FUNCLOG};

// デストラクタ
MapObjectFactory::~MapObjectFactory() {FUNCLOG};

// MapObjectListを生成して返す
MapObjectList* MapObjectFactory::createMapObjectList(experimental::TMXTiledMap* tiledMap)
{
    if(!tiledMap) return nullptr;
    
    // 自身を生成
    MapObjectFactory* p {new(nothrow) MapObjectFactory()};
    
    // レイヤ別に処理が分かれるので用意
    map<MapObjectFactory::Group, string> typeToString
    {
        {MapObjectFactory::Group::COLLISION, "collision"},
        {MapObjectFactory::Group::EVENT, "event"},
        //{MapObjectFactory::Group::CHARACTER, "Chara(object)"},
    };
    
    // グループごとに生成メソッドを用意
    map<Group, function<MapObject*(const ValueMap&)>> typeToFunc
    {
        {Group::COLLISION, CC_CALLBACK_1(MapObjectFactory::createObjectOnCollision, p)},
        {Group::EVENT, CC_CALLBACK_1(MapObjectFactory::createObjectOnEvent, p)},
        //{Group::CHARACTER, CC_CALLBACK_1(MapObjectFactory::createObjectOnCharacter, p)},
    };
    
    // ベクタを用意
    Vector<MapObject*> mapObjects {};
    
    for(int i {0}; i < static_cast<int>(MapObjectFactory::Group::SIZE); i++)
    {
        MapObjectFactory::Group group {static_cast<MapObjectFactory::Group>(i)};
        ValueVector infos {tiledMap->getObjectGroup(typeToString.at(group))->getObjects()};
        for(cocos2d::Value info : infos)
        {
            mapObjects.pushBack(typeToFunc[group](info.asValueMap()));
        }
    }
    
    // delete
    delete p;
    
    // MapObjectListを生成して返す
    return MapObjectList::create(mapObjects);
}

// オブジェクトの位置、大きさを取得
Rect MapObjectFactory::getRect(const ValueMap& info) const
{
    return Rect(info.at("x").asInt(), info.at("y").asInt(), info.at("width").asInt(), info.at("height").asInt());
}

// オブジェクトIDを取得
int MapObjectFactory::getObjectId(const ValueMap& info) const
{
    return (info.count("objID") != 0)?info.at("objID").asInt():static_cast<int>(ObjectID::UNDIFINED);
}

// イベントIDを取得
int MapObjectFactory::getEventId(const ValueMap& info) const
{
    return (info.count("EventID") != 0)?info.at("EventID").asInt():static_cast<int>(EventID::UNDIFINED);
}

// オブジェクトの種類名を取得
string MapObjectFactory::getObjectType(const ValueMap& info) const
{
    return info.at("type").asString();
}

// トリガーを取得
Trigger MapObjectFactory::getTrigger(const ValueMap& info) const
{
    return (info.count("trigger") != 0)?static_cast<Trigger>(info.at("trigger").asInt()):Trigger::SIZE;
}

// キャラクターIDを取得
int MapObjectFactory::getCharacterId(const ValueMap& info) const
{
    return (info.count("CharaID") != 0)?info.at("CharaID").asInt():static_cast<int>(CharacterID::UNDIFINED);
}

// キャラクターの動き方を取得
CharacterMovePattern MapObjectFactory::getCharacterMovePattern(const ValueMap& info) const
{
    return (info.count("movePattern") != 0)?static_cast<CharacterMovePattern>(info.at("movePattern").asInt()):CharacterMovePattern::SIZE;
}

// 向きを取得
Direction MapObjectFactory::getDirection(const ValueMap& info) const
{
    if(info.count("direction") != 0) return Direction::SIZE;
    
    map<string, Direction> stringToDirection
    {
        {string("RIGHT"), Direction::RIGHT},
        {string("LEFT"), Direction::LEFT},
        {string("UP"), Direction::BACK},
        {string("DOWN"), Direction::FRONT},
    };
    
    if(stringToDirection.count(info.at("direction").asString()) == 0) return Direction::SIZE;
    
    return stringToDirection.at(info.at("direction").asString());
}

// 当たり判定レイヤにあるオブジェクトを生成
MapObject* MapObjectFactory::createObjectOnCollision(const ValueMap& info)
{
    Rect rect {this->getRect(info)};
    MapObject* pObj = EventObject::create();
    pObj->setPosition(rect.origin + rect.size / 2);
    pObj->setContentSize(rect.size);
    pObj->setHit(true);
    pObj->setCollisionRect(Rect(0, 0, rect.size.width, rect.size.height));
    
    return pObj;
}

// イベントレイヤにあるオブジェクトを生成
MapObject* MapObjectFactory::createObjectOnEvent(const ValueMap& info)
{
    Rect rect {this->getRect(info)};
    
    // 入れ物を用意
    MapObject* pObj {nullptr};
    
    // オブジェクトの種類を取得
    string type { this->getObjectType(info) };
    
    // 種類が空の場合は単なるイベントのトリガーとして処理
    if(type == "")
    {
        pObj = EventObject::create();
        pObj->setEventId(this->getEventId(info));
        pObj->setTrigger(this->getTrigger(info));
    }
    
    pObj->setContentSize(rect.size);
    pObj->setPosition(rect.origin + rect.size / 2);
    pObj->setCollisionRect(Rect(0, 0, rect.size.width, rect.size.height));
    
    return pObj;
}

// キャラクターレイヤにあるオブジェクトを生成
MapObject* MapObjectFactory::createObjectOnCharacter(const ValueMap& info)
{
    Rect rect {this->getRect(info)};
    Character* chara {Character::create(this->getCharacterId(info), this->getDirection(info))};
    chara->setHit(true);
    chara->setContentSize(rect.size);
    chara->setPosition(rect.origin + rect.size / 2);
    chara->setCollisionRect(Rect(0, 0, rect.size.width, rect.size.height));
    
    return chara;
}