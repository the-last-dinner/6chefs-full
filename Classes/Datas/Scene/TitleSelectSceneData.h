//
//  TitleSelectSceneData.h
//  6chefs
//
//  Created by Kohei Asami on 2017/09/04.
//
//

#ifndef TitleSelectSceneData_h
#define TitleSelectSceneData_h

#include "Datas/Scene/SceneData.h"

class TitleSelectSceneData : public SceneData
{
// クラスメソッド
public:
    CREATE_FUNC(TitleSelectSceneData)

// インスタンスメソッド
private:
    TitleSelectSceneData();
    ~TitleSelectSceneData();
    virtual bool init();
};

#endif /* TitleSelectSceneData_h */
