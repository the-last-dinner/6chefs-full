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
// インスタンスメソッド
protected:
    TerrainObject();
    ~TerrainObject();
public:
    virtual void onWillMove(MapObject* target, const vector<Direction>& directions, function<void()> onMoved, const float ratio) = 0;
    virtual float getStaminaConsumptionRate() const = 0;
    virtual bool canDash() const = 0;
    virtual bool consumeStaminaWalking() const = 0;
};

#endif /* TerrainObject_h */
