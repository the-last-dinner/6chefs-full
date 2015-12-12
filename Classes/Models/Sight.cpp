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

// 弧度法から度数法に変換
float Sight::toDegree(const float radian) const
{
    return (radian * 180.f) / 3.14159265359f;
}

// 対象が視界内にいるか
bool Sight::isIn(MapObject* target, MapObjectList* list) const
{
    // キャラクタの向いている向きのベクトルを取得
    Vec2 v1 { MapUtils::getGridVector(this->chara->getDirection()) };
    
    // キャラクタから対象の間にできるベクトル
    Vec2 v2 { target->getPosition() - this->chara->getPosition() };
    
    // 視界限界距離より遠くにいれば視界外
    if(v2.getLength() > this->limitDistance) return false;
    
    // 二本のベクトルの間にできる角度を取得
    float degree { this->toDegree(v1.getAngle(v2)) };
    
    // 視野角の半分に収まっていなければ視界外
    if(degree > this->angle / 2) return false;
    
    return true;
}