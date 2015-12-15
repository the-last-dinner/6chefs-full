//
//  EndingScene.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/03.
//
//

#ifndef EndingScene_h
#define EndingScene_h

#include "Scenes/BaseScene.h"

class EndingScene : public BaseScene
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(EndingScene, const int)
private:
    EndingScene();
    ~EndingScene();
    bool init(const int endingId);
    virtual void onEnter() override;
    virtual void onPreloadFinished(LoadingLayer* loadingLayer) override;
    
// インスタンス変数
private:
    int end_id {0};
};

#endif /* EndingScene_h */
