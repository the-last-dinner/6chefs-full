//
//  DungeonMenuScene.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/10/04.
//
//

#ifndef __LastSupper__DungeonMenuScene__
#define __LastSupper__DungeonMenuScene__

#include "Scenes/baseScene.h"

class DungeonMainMenuLayer;

class DungeonMenuScene : public baseScene
{
// クラスメソッド
public:
    static Scene* createScene(Texture2D* screen);
    CREATE_FUNC_WITH_PARAM(DungeonMenuScene, Texture2D*);
// インスタンス変数
private:
    DungeonMainMenuLayer* mainMenu {nullptr};
    function<void()> onPopMenuScene;
    
// インスタンスメソッド
public:
    void onMenuHidden();
private:
    DungeonMenuScene();
    ~DungeonMenuScene();
    bool init(Texture2D* screen);
    virtual void onPreloadFinished() override;
    virtual void onCursorKeyPressed(const Key& key) override;
    virtual void onSpaceKeyPressed() override;
    virtual void onMenuKeyPressed() override;
    virtual void intervalInputCheck(const vector<Key>& keys);
};

#endif /* defined(__LastSupper__DungeonMenuScene__) */
