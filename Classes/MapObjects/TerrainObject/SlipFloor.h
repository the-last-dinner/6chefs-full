//
//  SlipFloor.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#ifndef SlipFloor_h
#define SlipFloor_h

#include "MapObjects/TerrainObject/TerrainObject.h"

class SlipFloor : public TerrainObject
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(SlipFloor, const Location&)
    
// インスタンスメソッド
private:
    SlipFloor();
    ~SlipFloor();
    virtual bool init(const Location& location) override;
    
public:
    virtual TerrainObject* clone(MapObject* target);
};

#endif /* SlipFloor_h */
