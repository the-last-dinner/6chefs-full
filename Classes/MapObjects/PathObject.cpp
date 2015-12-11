//
//  PathObject.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#include "MapObjects/PathObject.h"

// コンストラクタ
PathObject::PathObject() { FUNCLOG };

// デストラクタ
PathObject::~PathObject() { FUNCLOG };

// 初期化
bool PathObject::init()
{
    if(!MapObject::init()) return false;
    
    return true;
}

// 次のオブジェクトを設定
void PathObject::setNext(PathObject* next)
{
    this->next = next;
}

// 次のオブジェクトを取得
PathObject* PathObject::getNext() const
{
    return this->next;
}
