//
//  MapObjectFactory.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#include "MapObjects/MapObjectFactory.h"

#include "Objects.h"

// コンストラクタ
MapObjectFactory::MapObjectFactory() {FUNCLOG};

// デストラクタ
MapObjectFactory::~MapObjectFactory() {FUNCLOG};

// 初期化
bool MapObjectFactory::init()
{
    return true;
}

// 外部から呼び出してMapObjectを返すfactoryメソッド
MapObject* MapObjectFactory::createMapObject(const Group& group, const ValueMap& info)
{
    if(group == Group::SIZE) return nullptr;
    
    map<Group, function<MapObject*(const ValueMap&)>> typeToFunc
    {
        {Group::COLLISION, CC_CALLBACK_1(MapObjectFactory::createObjectOnCollision, this)},
        {Group::EVENT, CC_CALLBACK_1(MapObjectFactory::createObjectOnEvent, this)},
    };
    
    return typeToFunc.at(group)(info);
}

// オブジェクトの位置、大きさを取得
Rect MapObjectFactory::getRect(const ValueMap& info)
{
    return Rect(info.at("x").asInt(), info.at("y").asInt(), info.at("width").asInt(), info.at("height").asInt());
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
    string type = info.at("type").asString();
    
    // EventID取得
    int eventId = (info.count("EventID") != 0)?info.at("EventID").asInt():MapObject::EventID::UNDIFINED;
    
    // trigger取得
    Trigger trigger = (info.count("trigger") != 0)?static_cast<Trigger>(info.at("trigger").asInt()):Trigger::SIZE;
    
    // 種類が空の場合は単なるイベントのトリガーとして処理
    if(type == "")
    {
        pObj = EventObject::create();
        pObj->setEventId(eventId);
        pObj->setTrigger(trigger);
    }else if(type == "chara")
    {
        // オブジェクトのID取得
        int id = info.at("objID").asInt();
        
        pObj = Character::create(id, static_cast<Direction>(info.at("direction").asInt()));
        pObj->setHit(true);
    }
    
    pObj->setContentSize(rect.size);
    pObj->setPosition(rect.origin + rect.size / 2);
    pObj->setCollisionRect(Rect(0, 0, rect.size.width, rect.size.height));
    
    return pObj;
}