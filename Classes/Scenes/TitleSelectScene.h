//
//  TitleSelectScene.hpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/03.
//
//

#ifndef TitleSelectScene_h
#define TitleSelectScene_h

#include "define.h"
#include "Scenes/BaseScene.h"

class TitleSelectScene : public BaseScene
{
// クラスメソッド
public:
    CREATE_FUNC(TitleSelectScene)

// インスタンスメソッド
private:
    virtual bool init() override;
    virtual void onPreloadFinished(LoadingLayer* loadingLayer) override;
public:
    TitleSelectScene();
    ~TitleSelectScene();
    void onTitleSelected(int titleID);
};

#endif /* TitleSelectScene_h */
