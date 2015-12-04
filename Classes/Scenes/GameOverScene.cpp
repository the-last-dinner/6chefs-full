//
//  GameOverScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/02.
//
//

#include "Scenes/GameOverScene.h"

#include "Layers/LoadingLayer.h"

#include "Datas/Scene/GameOverSceneData.h"

// コンストラクタ
GameOverScene::GameOverScene() {FUNCLOG};

// デストラクタ
GameOverScene::~GameOverScene() {FUNCLOG};

// 初期化
bool GameOverScene::init(const Type type)
{
    return BaseScene::init(GameOverSceneData::create());
}

// シーン切り替え完了時
void GameOverScene::onEnter()
{
    BaseScene::onEnter();
    
    SoundManager::getInstance()->playSE("blood.wav");
    
    Sprite* blood {Sprite::create()};
    blood->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    blood->setColor(Color3B(177, 0, 0));
    blood->setPosition(WINDOW_CENTER);
    this->addChild(blood, Priority::LOADING_LAYER);
    this->bloodCover = blood;
}

// リソースのプリロード完了時
void GameOverScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    loadingLayer->onLoadFinished();
    
    this->bloodCover->runAction(Sequence::createWithTwoActions(FadeOut::create(0.4f), RemoveSelf::create()));
    
    SoundManager::getInstance()->playSE("gameover.wav");
    
    Sprite* bloodFrame {Sprite::createWithSpriteFrameName("blood2.png")};
    bloodFrame->setPosition(WINDOW_CENTER);
    bloodFrame->setScale(bloodFrame->getContentSize().width / WINDOW_WIDTH, bloodFrame->getContentSize().height / WINDOW_HEIGHT);
    this->addChild(bloodFrame);
}
