//
//  SlipFloor.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#include "MapObjects/TerrainObject/SlipFloor.h"

// コンストラクタ
SlipFloor::SlipFloor() {FUNCLOG};

// デストラクタ
SlipFloor::~SlipFloor() {FUNCLOG};

// 初期化
bool SlipFloor::init()
{
    return true;
}

// 複製
TerrainObject* SlipFloor::clone(MapObject* target)
{
    SlipFloor* p { SlipFloor::create() };
    
    p->setTarget(target);
    
    return p;
}