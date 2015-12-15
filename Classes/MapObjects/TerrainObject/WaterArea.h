//
//  WaterArea.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#ifndef Water_h
#define Water_h

#include "MapObjects/TerrainObject/TerrainObject.h"

class WaterArea : public TerrainObject
{
// クラスメソッド
public:
    CREATE_FUNC(WaterArea)

// インスタンスメソッド
private:
    WaterArea();
    ~WaterArea();
    bool init();
public:
    virtual void onWillMove(MapObject* target, const vector<Direction>& directions, function<void()> onMoved, const float ratio);
    virtual float getStaminaConsumptionRate() const { return 6.0f; };
    virtual bool canDash() const { return false; };
    virtual bool consumeStaminaWalking() const { return true; };
};

#endif /* Water_h */
