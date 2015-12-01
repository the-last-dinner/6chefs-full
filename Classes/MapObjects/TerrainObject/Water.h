//
//  Water.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#ifndef Water_h
#define Water_h

#include "MapObjects/TerrainObject/TerrainObject.h"

class Water : public TerrainObject
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Water, const Location&)
// インスタンス変数
// インスタンスメソッド
private:
    Water();
    ~Water();
    virtual bool init(const Location& location) override;
public:
    virtual TerrainObject* clone(MapObject* target);
};

#endif /* Water_h */
