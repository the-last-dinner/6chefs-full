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
    target->move(directions, onMoved, ratio / 4);
    target->getSprite()->setVisible(false);
    
//
//    Sprite* rect {Sprite::create()};
//    rect->setTextureRect(Rect(0,0,GRID * 2, GRID));
//    
//    ClippingNode* node {ClippingNode::create()};
//    node->setAlphaThreshold(0.1f);
//    node->setStencil(rect);
//    
//    target->addChild(node);
//    node->addChild( Sprite::createWithSpriteFrame(target->getSpriteFrames().at(etoi(target->getDirection()))) );
    
    
}