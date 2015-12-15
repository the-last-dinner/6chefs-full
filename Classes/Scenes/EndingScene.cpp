//
//  EndingScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/03.
//
//

#include "Scenes/EndingScene.h"

#include "Datas/Scene/EndingSceneData.h"
#include "Layers/LoadingLayer.h"

// コンストラクタ
EndingScene::EndingScene() {FUNCLOG};

// デストラクタ
EndingScene::~EndingScene() {FUNCLOG};

// 初期化
bool EndingScene::init(const int endingId)
{
    return BaseScene::init(EndingSceneData::create());
}

// シーン切り替え終了時
void EndingScene::onEnter()
{
    BaseScene::onEnter();
}

// リソースのプリロード完了時
void EndingScene::onPreloadFinished(LoadingLayer* loadingLayer)
{
    vector<string> credits_name = {
        "--BGM素材--",
        "魔王魂",
        "クラシック名曲\nサウンドライブラリー",
        "--効果音素材--",
        "効果音ラボ",
        "ポケットサウンド",
        "フリー音楽素材\nSenses Circuit",
        "---画像素材---",
        "ドット絵世界",
        "すきまの素材",
        "臼井の会",
        "ぴぽや",
        "-RyU-",
        "sorairobaibai",
        "とまりぎ",
        "水晶と月の家",
        "First Seed Material",
        "なにかしらツクール",
        "尾羽の小屋",
        "茫然の流もの喫茶",
        "白螺子屋",
        "イベントグラフィック\nどみず",
        "ジェダイマスター\nエンジニア\nナニヲ",
        "真夏大好き\nエンジニア\nいのす",
        "孫一ペロペロ\nデザイン\n早乙女",
        "ピクセル\nアート\nおぐぐ",
        "マエストロ\nプランナー\nスズラン",
        "制作\n最後の晩餐"
    };
    vector<string> pictures_name = {
        "epilogue.png",
        "chapter1.png",
        "daigoro_usually.png",
        "dandan_usually.png",
        "chapter2.png",
        "nadeshiko_usually.png",
        "ranmaru_usually.png",
        "chapter3.png",
        "yuki_stan.png",
        "manaka_usually.png",
        "chapter4.png",
        "taihou_usually.png",
        "chapter5.png",
        "magoichi_usually.png",
    };
    
    // 背景
    Sprite* background {Sprite::createWithSpriteFrameName("background.png")};
    background->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    this->addChild(background);
    
    // 文字
    vector<Label*> credits {};
    int len = credits_name.size();
    float x = WINDOW_WIDTH * 2 / 3;
    for (int i = 0; i < len; i++)
    {
        Label* label {Label::createWithTTF(credits_name[i], Resource::Font::MESSAGE, 48)};
        label->setPosition(x, -1 * label->getContentSize().height / 2);
        label->setColor(Color3B::WHITE);
        this->addChild(label);
        credits.push_back(label);
    }
    
    // 画像
    vector<Sprite*> pictures {};
    len = pictures_name.size();
    
    Sprite* sprite {Sprite::create(Resource::SpriteFrame::BASE_PATH + "disp/" + pictures_name[0])};
    sprite->setOpacity(0);
    sprite->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    this->addChild(sprite);
    pictures.push_back(sprite);
    
    x = WINDOW_WIDTH / 3;
    float y = WINDOW_HEIGHT / 2;
    float scale = 0.5;
    for (int i = 1; i < len; i++)
    {
        Sprite* sprite {Sprite::create(Resource::SpriteFrame::BASE_PATH + "disp/" + pictures_name[i])};
        sprite->setOpacity(0);
        sprite->setScale(scale);
        sprite->setPosition(x, y);
        this->addChild(sprite);
        pictures.push_back(sprite);
    }
    
    // 画像の動き
    Vector<FiniteTimeAction*> picture_acts {};
    picture_acts.pushBack(TargetedAction::create(pictures[0], FadeIn::create(1.f)));
    picture_acts.pushBack(TargetedAction::create(pictures[0], DelayTime::create(13.f)));
    picture_acts.pushBack(TargetedAction::create(pictures[0], FadeOut::create(1.f)));
    for (int i = 1; i < len; i++)
    {
        picture_acts.pushBack(TargetedAction::create(pictures[i], FadeIn::create(1.f)));
        picture_acts.pushBack(TargetedAction::create(pictures[i], DelayTime::create(4.7f)));
        picture_acts.pushBack(TargetedAction::create(pictures[i], FadeOut::create(1.f)));
    }
    
    loadingLayer->onLoadFinished();
    SoundManager::getInstance()->playBGM("ending.mp3");
    this->runAction(Sequence::create(picture_acts));
}

