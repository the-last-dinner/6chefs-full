//
//  MapObjectList.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#include "MapObjects/MapObjectList.h"

#include "MapObjects/MapObject.h"

// コンストラクタ
MapObjectList::MapObjectList() {FUNCLOG};

// デストラクタ
MapObjectList::~MapObjectList()
{
    FUNCLOG

    this->mapObjects.clear();
};

// 初期化
bool MapObjectList::init(const Vector<MapObject*>& mapObjects)
{
    this->mapObjects = mapObjects;
    
    return true;
}

// 指定IDのマップオブジェクトを取得
MapObject* MapObjectList::getMapObject(int objId) const
{
    for(MapObject* obj : this->mapObjects)
    {
        if(objId == obj->getObjectId())
        {
            return obj;
        }
    }
    
    return nullptr;
}

// マップオブジェクトのベクタを取得
const Vector<MapObject*>& MapObjectList::getMapObjects() const
{
    return this->mapObjects;
}

// 指定範囲内にあるマップオブジェクトのベクタを取得
Vector<MapObject*> MapObjectList::getMapObjects(const Rect& rect) const
{
    Vector<MapObject*> mapObjects {};
    for(MapObject* obj : this->mapObjects)
    {
        if(rect.intersectsRect(obj->getCollisionRect())) mapObjects.pushBack(obj);
    }
    
    return mapObjects;
}

// 指定座標を含むマップオブジェクトのベクタを取得
Vector<MapObject*> MapObjectList::getMapObjects(const Point& position) const
{
    Vector<MapObject*> mapObjects {};
    for(MapObject* obj : this->mapObjects)
    {
        if(obj->getCollisionRect().containsPoint(position)) mapObjects.pushBack(obj);
    }
    
    return mapObjects;
}

// 指定範囲内にあたり判定を持つマップオブジェクトが存在するか
const bool MapObjectList::containsCollisionObject(const Rect& rect) const
{
    for(MapObject* obj : this->getMapObjects(rect))
    {
        if(obj->isHit()) return true;
    }
    
    return false;
}

// マップオブジェクトを追加
void MapObjectList::add(MapObject* mapObject)
{
    this->mapObjects.pushBack(mapObject);
}

// 主人公を設定
void MapObjectList::setMainCharacter(Character* mainChara)
{
    this->mainCharacter = mainChara;
}

// 主人公を取得
Character* MapObjectList::getMainCharacter() const
{
    return this->mainCharacter;
}