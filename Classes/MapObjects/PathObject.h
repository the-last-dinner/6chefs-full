//
//  PathObject.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/09.
//
//

#ifndef PathObject_h
#define PathObject_h

#include "MapObjects/MapObject.h"

class PathObject : public MapObject
{
// クラスメソッド
public:
    CREATE_FUNC(PathObject)
    
// インスタンス変数
private:
    PathObject* previous { nullptr };
    PathObject* next { nullptr };
    
// インスタンスメソッド
private:
    PathObject();
    ~PathObject();
    bool init();
    void setPrevious(PathObject* previous);
    void setNext(PathObject* next);
    PathObject* getPrevious() const;
    PathObject* getNext() const;
    
};

#endif /* PathObject_h */
