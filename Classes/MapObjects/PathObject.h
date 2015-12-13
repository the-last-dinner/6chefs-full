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
    int pathId { -1 };
    int previousId { -1 };
    int nextId { -1 };
    
// インスタンスメソッド
private:
    PathObject();
    ~PathObject();
    bool init();
public:
    void setPathId(int pathId);
    void setPreviousId(int previousId);
    void setNextId(int nextId);
    int getPathId() const;
    int getPreviousId() const;
    int getNextId() const;
};

#endif /* PathObject_h */
