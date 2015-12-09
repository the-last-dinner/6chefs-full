//
//  ItemObject.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#include "MapObjects/ItemObject.h"

// 定数
const string ItemObject::PREFIX { "item_" };
const string ItemObject::BLUE {"blue_"};

// コンストラクタ
ItemObject::ItemObject() {FUNCLOG};

// デストラクタ
ItemObject::~ItemObject() {FUNCLOG};

// 初期化
bool ItemObject::init()
{
    if(!MapObject::init()) return false;
    
    
    
    return true;
}
