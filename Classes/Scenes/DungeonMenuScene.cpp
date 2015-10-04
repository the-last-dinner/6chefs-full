//
//  DungeonMenuScene.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/10/04.
//
//

#include "Scenes/DungeonMenuScene.h"
#include "Layers/Menu/DungeonMainMenuLayer.h"

// コンストラクタ
DungeonMenuScene::DungeonMenuScene(){FUNCLOG}

// デストラクタ
DungeonMenuScene::~DungeonMenuScene(){FUNCLOG}

// シーン生成
Scene* DungeonMenuScene::createScene(Texture2D* screen)
{
    Scene* scene = Scene::create();
    DungeonMenuScene* layer = DungeonMenuScene::create(screen);
    scene->addChild(layer);
    return scene;
}

// 初期化
bool DungeonMenuScene::init(Texture2D* screen)
{
    FUNCLOG
    
    //スクショを生成
    Sprite* screenSprite = Sprite::createWithTexture(screen);
    //screenSprite->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    screenSprite->setPosition(WINDOW_CENTER);
    screenSprite->setFlippedY(true);
    this->addChild(screenSprite);
    
    // メインメニューレイヤーを生成
    DungeonMainMenuLayer* menu = DungeonMainMenuLayer::create();
    menu->onMenuHidden = CC_CALLBACK_0(DungeonMenuScene::onMenuHidden, this);
    this->addChild(menu);
    this->mainMenu = menu;
    this->mainMenu->show();
    return true;
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

