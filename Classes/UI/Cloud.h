//
//  Cloud.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/04.
//
//

#ifndef Cloud_h
#define Cloud_h

#include "define.h"

class Cloud : public Node
{
// 定数
private:
    static const float MARGIN;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Cloud, const Size&)

// インスタンスメソッド
private:
    Cloud();
    ~Cloud();
    bool init(const Size& size);
};

#endif /* Cloud_h */
