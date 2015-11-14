//
//  MapObjectList.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#ifndef __LastSupper__MapObjectList__
#define __LastSupper__MapObjectList__

#include "Common.h"

#include "MapObjects/MapObject.h"

class Character;
class MapObject;

class MapObjectList : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_TWO_PARAM(MapObjectList, const Vector<MapObject*>&, const Vector<MapObject*>&)
    
// インスタンス変数
private:
    Vector<MapObject*> availableObjects {};
    Vector<MapObject*> disableObjects {};
    
// インスタンスメソッド
private:
    MapObjectList();
    ~MapObjectList();
    bool init(const Vector<MapObject*>& availableObjects, const Vector<MapObject*> disableObjects);
public:
    MapObject* getMapObject(int objId) const;
    MapObject* getMapObjectFromDisableList(int objId) const;
    const Vector<MapObject*>& getMapObjects() const;
    const bool containsCollisionObject(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Point& position) const;
    Vector<MapObject*> getMapObjectsByGridRect(const Rect& gridRect, const Trigger trigger = Trigger::SIZE) const;
    
    vector<int> getEventIds(const Trigger trigger) const;
    vector<Rect> getGridCollisionRects() const;
    void add(MapObject* mapObject);
    void remove(MapObject* mapObject);
};

#endif /* defined(__LastSupper__MapObjectList__) */
