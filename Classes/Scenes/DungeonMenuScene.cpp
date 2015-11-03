//
//  DungeonMenuScene.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/10/04.
//
//

#include "Scenes/DungeonMenuScene.h"
#include "Layers/Menu/DungeonMainMenuLayer.h"
#include "Layers/Menu/SaveDataSelector.h"
#include "Layers/Menu/ItemMenuLayer.h"

// コンストラクタ
DungeonMenuScene::DungeonMenuScene(){FUNCLOG}

// デストラクタ
DungeonMenuScene::~DungeonMenuScene(){FUNCLOG}

// シーン生成
Scene* DungeonMenuScene::createScene(Texture2D* screen, function<void()> onPopMenuScene)
{
    Scene* scene = Scene::create();
    DungeonMenuScene* layer = DungeonMenuScene::create(screen, onPopMenuScene);
    scene->addChild(layer);
    return scene;
}

// 初期化
bool DungeonMenuScene::init(Texture2D* screen, function<void()> onPopMenuScene)
{
    FUNCLOG
    // メニューシーンをポップする際の処理
    this->onPopMenuScene = onPopMenuScene;
    // スクショを生成
    Sprite* screenSprite = Sprite::createWithTexture(screen);
    screenSprite->setScale(Director::getInstance()->getWinSize().width / screenSprite->getContentSize().width);
    screenSprite->setPosition(WINDOW_CENTER);
    this->addChild(screenSprite);
    
    // メインメニューレイヤーを生成
    this->createMainMenu();
    
    return true;
}

// メインメニューレイヤー生成
void DungeonMenuScene::createMainMenu()
{
    FUNCLOG
    DungeonMainMenuLayer* menu = DungeonMainMenuLayer::create();
    menu->onSaveMenuSelected = CC_CALLBACK_0(DungeonMenuScene::onSaveMenuSelected, this);
    menu->onMenuHidden = CC_CALLBACK_0(DungeonMenuScene::onMenuHidden, this);
    menu->onItemMenuSelected = CC_CALLBACK_0(DungeonMenuScene::onItemMenuSelected, this);
    this->addChild(menu);
    this->mainMenu = menu;
    this->mainMenu->show();
}

// セーブデータ選択レイヤーの生成
void DungeonMenuScene::createSaveMenu()
{
    FUNCLOG
    SaveDataSelector* saveDataSelector { SaveDataSelector::create(true) };
    this->addChild(saveDataSelector);
    // セーブデータ選択レイヤーのイベントをリッスン
    saveDataSelector->onSaveDataSelectCancelled = CC_CALLBACK_0(DungeonMenuScene::onSaveDataSelectCancelled, this);
    saveDataSelector->hide();
    this->saveDataSelector = saveDataSelector;
}

void DungeonMenuScene::createItemMenu()
{
    FUNCLOG
    ItemMenuLayer* itemMenu { ItemMenuLayer::create()};
    this->addChild(itemMenu);
    itemMenu->hide();
    itemMenu->onItemMenuCanceled = CC_CALLBACK_0(DungeonMenuScene::onItemMenuCanceled, this);
    this->itemMenu = itemMenu;
}

void DungeonMenuScene::onPreloadFinished()
{
}

// 方向キーを押した時
void DungeonMenuScene::onCursorKeyPressed(const Key& key)
{
}

// スペースキーを押した時
void DungeonMenuScene::onSpaceKeyPressed()
{
}



// キーを押し続けている時
void DungeonMenuScene::intervalInputCheck(const vector<Key>& keys)
{
}

// メニューキー押したとき
void DungeonMenuScene::onMenuKeyPressed()
{
}

//メニューが削除されたとき
void DungeonMenuScene::onMenuHidden()
{
    FUNCLOG
    if(this->onPopMenuScene)
    {
        this->onPopMenuScene();
    }
    Director::getInstance()->popScene();
}

#pragma mark -
#pragma mark SaveDataSelecter

// セーブメニューが選択された時
void DungeonMenuScene::onSaveMenuSelected()
{
    FUNCLOG
    this->mainMenu->hide();
    this->createSaveMenu();
    this->saveDataSelector->show();
}

// セーブデータが選ばれた時
void DungeonMenuScene::onSaveDataSelected(int dataId)
{
    FUNCLOG
    //PlayerDataManager::getInstance()->setMainLocalData(dataId);
    //SoundManager::getInstance()->playSound("se/failure.mp3");
}

// セーブデータ選択をキャンセルした時
void DungeonMenuScene::onSaveDataSelectCancelled()
{
    FUNCLOG
    SoundManager::getInstance()->playSound("se/back.mp3");
    runAction(Sequence::create(
        CallFunc::create([=](){this->saveDataSelector->hide();}),
        CallFunc::create([=](){this->mainMenu->show();}),
        nullptr
    ));
}

#pragma mark -
#pragma mark ItemMenu

// アイテムメニューが選択された時
void DungeonMenuScene::onItemMenuSelected()
{
    FUNCLOG
    this->mainMenu->hide();
    this->createItemMenu();
    this->itemMenu->show();
}

// アイテムメニューでキャンセルを押した時
void DungeonMenuScene::onItemMenuCanceled()
{
    FUNCLOG
    SoundManager::getInstance()->playSound("se/back.mp3");
    runAction(Sequence::create(
        CallFunc::create([=](){this->itemMenu->hide();}),
        CallFunc::create([=](){this->mainMenu->show();}),
        nullptr
    ));
}


