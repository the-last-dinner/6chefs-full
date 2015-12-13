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

// 前のオブジェクトを設定
void PathObject::setPrevious(PathObject* previous)
{
    this->previous = previous;
}

// 次のオブジェクトを設定
void PathObject::setNext(PathObject* next)
{
    this->next = next;
}

// 前のオブジェクトを取得
PathObject* PathObject::getPrevious() const
{
    return this->previous;
}

// 次のオブジェクトを取得
PathObject* PathObject::getNext() const
{
    return this->next;
}
