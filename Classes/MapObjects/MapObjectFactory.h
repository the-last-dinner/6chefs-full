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
    Rect getRect(const ValueMap& info);
    MapObject* createObjectOnCollision(const ValueMap& info);
    MapObject* createObjectOnEvent(const ValueMap& info);
    
public:
    MapObject* createMapObject(const Group& group, const ValueMap& info);
};

#endif /* defined(__LastSupper__MapObjectFactory__) */
