//
//  ItemObject.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#ifndef ItemObject_h
#define ItemObject_h

#include "MapObjects/MapObject.h"

class ItemObject : public MapObject
{
// 定数
private:
    static const string PREFIX;
    static const string BLUE;
    static const int ANIMATION_FRAME_NUM;
    
// クラスメソッド
public:
    CREATE_FUNC(ItemObject)
    
// インスタンスメソッド
public:
    ItemObject();
    ~ItemObject();
    bool init();
};

#endif /* ItemObject_h */
