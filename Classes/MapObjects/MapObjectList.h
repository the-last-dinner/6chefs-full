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

class Character;
class MapObject;

class MapObjectList : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(MapObjectList, const Vector<MapObject*>&)
    
// インスタンス変数
private:
    Vector<MapObject*> mapObjects {};
    Character* mainCharacter { nullptr };
    
// インスタンスメソッド
private:
    MapObjectList();
    ~MapObjectList();
    bool init(const Vector<MapObject*>&);
public:
    MapObject* getMapObject(int objId) const;
    const Vector<MapObject*>& getMapObjects() const;
    const bool containsCollisionObject(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Point& position) const;
    void add(MapObject* mapObject);
    
    void setMainCharacter(Character* mainChara);
    Character* getMainCharacter() const;
};

#endif /* defined(__LastSupper__MapObjectList__) */
