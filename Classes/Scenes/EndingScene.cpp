//
//  EndingScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/03.
//
//

#include "Scenes/EndingScene.h"

#include "Datas/Scene/EndingSceneData.h"
#include "Datas/Scene/DungeonSceneData.h"
#include "Scenes/DungeonScene.h"
#include "Layers/LoadingLayer.h"

// コンストラクタ
EndingScene::EndingScene() {FUNCLOG};

// デストラクタ
EndingScene::~EndingScene() {FUNCLOG};

// 初期化
bool EndingScene::init(const int endingId)
{
    this->end_id = endingId;
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
    vector<pair<string,float>> credits_name = {
        // ------------------
        {"--- BGM素材 ---",15.0},
        //
        {"魔王魂", 17.0},
        //
        {"クラシック名曲", 18.5},
        {"サウンドライブラリー", 19.0},
        // ------------------
        {"--- 効果音素材 ---", 23.0},
        //
        {"効果音ラボ", 24.5},
        //
        {"ポケットサウンド", 26.0},
        //
        {"フリー音楽素材", 27.5},
        {"Senses Circuit", 28.0},
        // ------------------
        {"--- 画像素材 ---", 32.0},
        //
        {"ドット絵世界", 33.5},
        //
        {"すきまの素材", 35.0},
        //
        {"臼井の会", 36.5},
        //
        {"ぴぽや",38.0},
        //
        {"-RyU-", 39.5},
        //
        {"sorairobaibai", 41.0},
        //
        {"とまりぎ", 42.5},
        //
        {"水晶と月の家", 44.0},
        //
        {"First Seed Material", 45.5},
        //
        {"なにかしらツクール", 47.0},
        //
        {"尾羽の小屋", 48.5},
        //
        {"茫然の流もの喫茶", 50.0},
        //
        {"白螺子屋", 51.5},
        // ------------------
        {"--- 制作メンバー ---", 55.0},
        //
        {"イベントグラフィック", 57.0},
        {"どみず", 58.0},
        //
        {"ジェダイマスター\n", 62.0},
        {"エンジニア", 62.5},
        {"ナニヲ", 63.5},
        //
        {"真夏大好き", 67.5},
        {"エンジニア",68.0},
        {"いのす", 69.0},
        //
        {"孫一ペロペロ", 73.5},
        {"キャラクターデザイナー", 74.0},
        {"早乙女", 75.0},
        //
        {"ピクセル", 79.5},
        {"アート", 80.0},
        {"おぐぐ", 81.0},
        //
        {"マエストロ", 86.0},
        {"プランナー", 86.5},
        {"スズラン", 87.5},
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
    Vector<FiniteTimeAction*> label_acts {};
    label_acts.pushBack(DelayTime::create(15.f));
    int credits_len = credits_name.size();
    
    float x = WINDOW_WIDTH * 4 / 5;
    float font_size = 28;
    float moving_time = 9.f;
    for (int i = 0; i < credits_len; i++)
    {
        Label* label {Label::createWithTTF(credits_name[i].first, Resource::Font::MESSAGE, font_size)};
        label->setPosition(x, -1 * label->getContentSize().height / 2);
        label->setColor(Color3B::WHITE);
        this->addChild(label);
        label_acts.pushBack(Sequence::createWithTwoActions(TargetedAction::create(label, DelayTime::create(credits_name[i].second)), TargetedAction::create(label, MoveTo::create(credits_name[i].second < 55 ? moving_time : (moving_time + 2.0), Vec2(label->getPosition().x, label->getContentSize().height / 2 + WINDOW_HEIGHT)))));
    }
    
    // 制作
    Label* last_label {Label::createWithTTF("制作", Resource::Font::MESSAGE, font_size)};
    last_label->setPosition(x, -1 * last_label->getContentSize().height / 2);
    last_label->setColor(Color3B::WHITE);
    this->addChild(last_label);
    last_label->runAction(Sequence::createWithTwoActions(DelayTime::create(92.5), MoveTo::create(5.5, Vec2(last_label->getPosition().x, last_label->getContentSize().height * 2.5 + WINDOW_HEIGHT / 2))));
    
    // ロゴ
    Sprite* logo {Sprite::createWithSpriteFrameName("the_last_dinner_log.png")};
    logo->setPosition(x, -1 * logo->getContentSize().height / 2);
    float scale_logo = 0.75;
    logo->setScale(scale_logo);
    this->addChild(logo);
    logo->runAction(Sequence::createWithTwoActions(DelayTime::create(93.0), MoveTo::create(5.0, Vec2(logo->getPosition().x, WINDOW_HEIGHT/2))));
    
    // 画像
    vector<Sprite*> pictures {};
    int pic_len = pictures_name.size();
    
    Sprite* sprite {Sprite::create(Resource::SpriteFrame::BASE_PATH + "disp/" + pictures_name[0])};
    sprite->setOpacity(0);
    sprite->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
    this->addChild(sprite);
    pictures.push_back(sprite);
    
    x = WINDOW_WIDTH / 3 - 20;
    float y = WINDOW_HEIGHT / 2;
    float scale = 0.5;
    for (int i = 1; i < pic_len; i++)
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
    for (int i = 1; i < pic_len; i++)
    {
        picture_acts.pushBack(TargetedAction::create(pictures[i], FadeIn::create(1.f)));
        if (i != pic_len - 1)
        {
            picture_acts.pushBack(TargetedAction::create(pictures[i], DelayTime::create(4.7f)));
            picture_acts.pushBack(TargetedAction::create(pictures[i], FadeOut::create(1.f)));
        }
    }
    
    // FadeOut用幕
    SpriteUtils::Square square = SpriteUtils::Square(0,0,100,100);
    Sprite* black {SpriteUtils::getSquareSprite(square, 0)};
    black->setOpacity(0);
    black->setColor(Color3B::BLACK);
    this->addChild(black);
    
    // エディング実行
    loadingLayer->onLoadFinished();
    SoundManager::getInstance()->playBGM("ending.mp3", false);
    this->runAction(Sequence::create(picture_acts));
    this->runAction(Spawn::create(label_acts));
    this->runAction(Sequence::create(DelayTime::create(103), TargetedAction::create(black, FadeIn::create(2.f)), CallFunc::create([this](){
        PlayerDataManager::getInstance()->setGameClear(this->end_id);
        Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocalData()->getLocation())));
    }), nullptr));
}

