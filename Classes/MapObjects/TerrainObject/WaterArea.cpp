//
//  WaterArea.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/01.
//
//

#include "MapObjects/TerrainObject/WaterArea.h"

// コンストラクタ
WaterArea::WaterArea() {FUNCLOG};

// デストラクタ
WaterArea::~WaterArea() {FUNCLOG};

// 初期化
bool WaterArea::init()
{
    return true;
}

// オブジェクトが動こうとした時
void WaterArea::onWillMove(MapObject* target, const vector<Direction>& directions, function<void()> onMoved, const float ratio)
{
    // 速度を1/2にして移動
    target->move(directions, onMoved, ratio / 2);
}