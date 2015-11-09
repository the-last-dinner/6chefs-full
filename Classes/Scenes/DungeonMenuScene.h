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
class SaveDataSelector;
class ItemMenuLayer;
class CharacterMenuLayer;

class DungeonMenuScene : public baseScene
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_TWO_PARAM(DungeonMenuScene, Texture2D*, function<void()>);
    
// クラス変数
private:
    static const string MAIN_LAYER_NAME;
    static const string SAVE_LAYER_NAME;
    static const string ITEM_LAYER_NAME;
    static const string CHARA_LAYER_NAME;

// インスタンス変数
public:
    function<void()> onPopMenuScene;
private:
    DungeonMainMenuLayer* mainMenu {nullptr};
    SaveDataSelector* saveDataSelector {nullptr};
    ItemMenuLayer* itemMenu {nullptr};
    CharacterMenuLayer* charaMenu {nullptr};
    int menuIndex {0};
    
// インスタンスメソッド
public:
    void onMenuHidden();
private:
    DungeonMenuScene();
    ~DungeonMenuScene();
    bool init(Texture2D* screen, function<void()> onPopMenuScene);
    virtual void onPreloadFinished() override;
    virtual void onCursorKeyPressed(const Key& key) override;
    virtual void onSpaceKeyPressed() override;
    virtual void onMenuKeyPressed() override;
    virtual void intervalInputCheck(const vector<Key>& keys);
    void createMainMenu();
    void createSaveMenu();
    void createItemMenu();
    void createCharaMenu();
    // メインメニュー
    void onSaveMenuSelected();
    void onItemMenuSelected();
    void onCharaMenuSelected();
    // セーブデータセレクター
    void onSaveDataSelectCancelled();
    // アイテムメニュー
    void onItemMenuCanceled();
    // キャラクターメニュー
    void onCharaMenuCanceled();
};

#endif /* defined(__LastSupper__DungeonMenuScene__) */
