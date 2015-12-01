//
//  TerrainObject.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#ifndef TerrainObject_h
#define TerrainObject_h

#include "MapObjects/MapObject.h"

class TerrainObject : public MapObject
{
// インスタンス変数
private:
    MapObject* target { nullptr };
    
// インスタンスメソッド
protected:
    TerrainObject();
    ~TerrainObject();
    virtual bool init(const Location& location);
    void setTarget(MapObject* target);
    MapObject* getTarget();
public:
    virtual TerrainObject* clone(MapObject* target) = 0;
};

#endif /* TerrainObject_h */
