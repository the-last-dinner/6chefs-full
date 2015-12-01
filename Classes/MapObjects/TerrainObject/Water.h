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
    CREATE_FUNC(Water)
// インスタンス変数
// インスタンスメソッド
private:
    Water();
    ~Water();
    bool init();
public:

};

#endif /* Water_h */
