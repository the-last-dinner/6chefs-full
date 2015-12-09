//
//  Sight.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#include "Models/Sight.h"

#include "MapObjects/MapObjectList.h"

// 定数
const float Sight::DEFAULT_VIEW_ANGLE { 90.f };
const int Sight::DEFAULT_GRID_LIMIT_DISTANCE { 10 };

// コンストラクタ
Sight::Sight() {FUNCLOG};

// デストラクタ
Sight::~Sight() {FUNCLOG};

// 初期化
bool Sight::init(Character* chara)
{
    this->chara = chara;
    
    return true;
}

// 対象が視界内にいるか
bool Sight::isIn(MapObject* target, MapObjectList* list)
{
    return false;
}