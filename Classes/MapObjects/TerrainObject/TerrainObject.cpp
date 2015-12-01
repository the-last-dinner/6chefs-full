//
//  TerrainObject.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#include "MapObjects/TerrainObject/TerrainObject.h"

// コンストラクタ
TerrainObject::TerrainObject() {};

// デストラクタ
TerrainObject::~TerrainObject() {};

// 上に乗るオブジェクトを格納
void TerrainObject::setTarget(MapObject* target)
{
    this->target = target;
}

// 上に乗っているオブジェクトを取得
MapObject* TerrainObject::getTarget()
{
    return this->target;
}