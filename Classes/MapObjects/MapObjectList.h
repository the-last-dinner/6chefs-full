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
    CREATE_FUNC(MapObjectList)
    CREATE_FUNC_WITH_PARAM(MapObjectList, const vector<MapObject*>&)
    
// インスタンス変数
private:
    vector<MapObject*> mapObjects {};
    Character* mainCharacter { nullptr };
    
// インスタンスメソッド
private:
    MapObjectList();
    ~MapObjectList();
    bool init();
    bool init(const vector<MapObject*>&);
public:
    MapObject* getMapObject(const Point& position) const;
    const vector<MapObject*>& getMapObjects() const;
    void add(MapObject* mapObject);
    
    void setMainCharacter(Character* mainChara);
    Character* getMainCharacter() const;
};

#endif /* defined(__LastSupper__MapObjectList__) */
