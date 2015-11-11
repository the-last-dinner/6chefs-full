//
//  MapObjectList.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#include "MapObjects/MapObjectList.h"

// コンストラクタ
MapObjectList::MapObjectList() {FUNCLOG};

// デストラクタ
MapObjectList::~MapObjectList()
{
    FUNCLOG

    this->availableObjects.clear();
    this->disableObjects.clear();
};

// 初期化
bool MapObjectList::init(const Vector<MapObject*>& availableObjects, const Vector<MapObject*> disableObjects)
{
    this->availableObjects = availableObjects;
    this->disableObjects = disableObjects;
    
    return true;
}

// 指定IDのマップオブジェクトを取得
MapObject* MapObjectList::getMapObject(int objId) const
{
    for(MapObject* obj : this->availableObjects)
    {
        if(objId == obj->getObjectId())
        {
            return obj;
        }
    }
    
    return nullptr;
}

// 無効リストから指定IDのマップオブジェクトを取得
MapObject* MapObjectList::getMapObjectFromDisableList(int objId) const
{
    for(MapObject* obj : this->disableObjects)
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
    return this->availableObjects;
}

// 指定範囲内にあるマップオブジェクトのベクタを取得
Vector<MapObject*> MapObjectList::getMapObjects(const Rect& rect) const
{
    Vector<MapObject*> mapObjects {};
    for(MapObject* obj : this->availableObjects)
    {
        if(rect.intersectsRect(obj->getCollisionRect())) mapObjects.pushBack(obj);
    }
    
    return mapObjects;
}

// 指定座標を含むマップオブジェクトのベクタを取得
Vector<MapObject*> MapObjectList::getMapObjects(const Point& position) const
{
    Vector<MapObject*> mapObjects {};
    for(MapObject* obj : this->availableObjects)
    {
        if(obj->getCollisionRect().containsPoint(position)) mapObjects.pushBack(obj);
    }
    
    return mapObjects;
}

// Rect(マス座標, マスサイズ)とトリガーからマップオブジェクトを取得
Vector<MapObject*> MapObjectList::getMapObjectsByGridRect(const Rect& gridRect, const Trigger trigger) const
{
    Vector<MapObject*> mapObjects {};
    bool needToCheckTrigger {trigger != Trigger::SIZE};
    
    for(MapObject* obj : this->availableObjects)
    {
        bool flag { false };
        
        Rect rect {obj->getGridRect()};
        
        if(MapUtils::intersectsGridRect(gridRect, rect))
        {
            if(!needToCheckTrigger) flag = true;
            
            if(obj->getTrigger() == trigger) flag = true;
        }
        
        if(flag) mapObjects.pushBack(obj);
    }
    
    return mapObjects;
}

// 指定トリガーのマップオブジェクトのEventIDベクタを取得
vector<int> MapObjectList::getEventIds(const Trigger trigger) const
{
    vector<int> eventIds {};
    
    for(MapObject* obj : this->availableObjects)
    {
        if(obj->getTrigger() == trigger) eventIds.push_back(obj->getEventId());
    }
    
    return eventIds;
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
    this->availableObjects.pushBack(mapObject);
    
    // 無効リストに存在する場合は削除
    for(MapObject* obj : this->disableObjects)
    {
        if(mapObject->getObjectId() == obj->getObjectId())
        {
            this->disableObjects.eraseObject(mapObject);
            
            break;
        }
    }
}
