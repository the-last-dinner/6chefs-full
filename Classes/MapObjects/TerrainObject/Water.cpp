//
//  Water.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#include "MapObjects/TerrainObject/Water.h"

// コンストラクタ
Water::Water() {FUNCLOG};

// デストラクタ
Water::~Water() {FUNCLOG};

// 初期化
bool Water::init()
{
    return true;
}

// 複製を生成
TerrainObject* Water::clone(MapObject* target)
{
    Water* p {Water::create()};
    
    p->setTarget(target);
    
    return p;
}