//
//  StartUpScene.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/13.
//
//

#include "Scenes/StartUpScene.h"
#include "Scenes/TitleScene.h"
#include "Datas/Scene/StartUpSceneData.h"
#include "Layers/LoadingLayer.h"

// 初期化
bool StartUpScene::init()
{
    if (!BaseScene::init(StartUpSceneData::create())) return false;
    
    return true;
}

// シーン生成直後
void StartUpScene::onEnter()
{
    BaseScene::onEnter();
}

// データ読み込み後
void StartUpScene::onPreloadFinished(LoadingLayer *loadingLayer)
{
    // ローディング終了
    loadingLayer->onLoadFinished();
    
    // ロゴ生成
    Sprite* logo {Sprite::createWithSpriteFrameName("the_last_dinner_log.png")};
    logo->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    logo->setScale(1.2f);
    logo->setOpacity(0);
    logo->setZOrder(1000);
    this->addChild(logo);
    
    // 効果音
    SoundManager::getInstance()->playSE("logo_display.mp3");
    
    // ロゴのアニメーション
    logo->runAction(Sequence::createWithTwoActions(FadeIn::create(0.5f),EaseCubicActionOut::create(TintTo::create(1.0f, Color3B::RED))));
    
    // シーンのアニメーション
    this->runAction(Sequence::create(DelayTime::create(2.0f), TargetedAction::create(logo,FadeOut::create(1.0f)),CallFunc::create([](){Director::getInstance()->replaceScene(TitleScene::create());}), nullptr));
}
