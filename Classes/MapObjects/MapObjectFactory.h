//
//  MapObjectFactory.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#ifndef __LastSupper__MapObjectFactory__
#define __LastSupper__MapObjectFactory__

#include "Common.h"

class MapObject;

class MapObjectFactory : public Ref
{
// 定数
public:
    enum struct Group
    {
        COLLISION,
        EVENT,
        //CHARACTER,
        
        SIZE,
    };
    
// クラスメソッド
public:
    CREATE_FUNC(MapObjectFactory)
    
// インスタンス変数
    
// インスタンスメソッド
private:
    MapObjectFactory();
    ~MapObjectFactory();
    bool init();
    Rect getRect(const ValueMap& info) const;
    int getObjectId(const ValueMap& info) const;
    int getEventId(const ValueMap& info) const;
    string getObjectType(const ValueMap& info) const;
    Trigger getTrigger(const ValueMap& info) const;
    int getCharacterId(const ValueMap& info) const;
    CharacterMovePattern getCharacterMovePattern(const ValueMap& info) const;
    Direction getDirection(const ValueMap& info) const;
    
    MapObject* createObjectOnCollision(const ValueMap& info);
    MapObject* createObjectOnEvent(const ValueMap& info);
    MapObject* createObjectOnCharacter(const ValueMap& info);
    
public:
    MapObject* createMapObject(const Group& group, const ValueMap& info);
};

#endif /* defined(__LastSupper__MapObjectFactory__) */
