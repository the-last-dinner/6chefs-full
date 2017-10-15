//
//  TitleSelectPanel.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#include "Layers/TitleSelect/TitleSelectPanel.h"
#include "Effects/Light.h"

// 定数
const map<TitleSelectPanel::TYPE, string> TitleSelectPanel::TYPE_TO_TITLE_SPRITE_FRAME_NAME {
    {TYPE::ONE, "title_select_1.png"},
    {TYPE::TWO, "title_select_2.png"},
};

const map<TitleSelectPanel::TYPE, string> TitleSelectPanel::TYPE_TO_CHARA_SPRITE_FRAME_NAME {
    {TYPE::ONE, "title_select_magoichi.png"},
    {TYPE::TWO, "title_select_yuki.png"},
};

const map<TitleSelectPanel::TYPE, Point> TitleSelectPanel::TYPE_TO_TITLE_POSITION {
    {TYPE::ONE, Point(60, 470)},
    {TYPE::TWO, Point(730, 130)},
};

const map<TitleSelectPanel::TYPE, Point> TitleSelectPanel::TYPE_TO_CHARA_POSITION {
    {TYPE::ONE, Point(80, 0)},
    {TYPE::TWO, Point(380, 0)},
};

const map<TitleSelectPanel::TYPE, Point> TitleSelectPanel::TYPE_TO_CURSOR_POSITION {
    {TYPE::ONE, Point(30, 90)},
    {TYPE::TWO, Point(30, 80)},
};

const int TitleSelectPanel::FOCUSED_CHARA_Z_ORDER { 100 };
const int TitleSelectPanel::UNFOCUSED_CHARA_Z_ORDER { 99 };

// コンストラクタ
TitleSelectPanel::TitleSelectPanel() { FUNCLOG }

// デストラクタ
TitleSelectPanel::~TitleSelectPanel() { FUNCLOG }

// 初期化
bool TitleSelectPanel::init(TYPE type)
{
    if (!Node::init()) return false;
    
    // タイトル名
    Sprite* title { Sprite::createWithSpriteFrameName(TYPE_TO_TITLE_SPRITE_FRAME_NAME.at(type)) };
    title->setPosition(TYPE_TO_TITLE_POSITION.at(type));
    this->addChild(title);
    
    // キャラ
    Sprite* chara { Sprite::createWithSpriteFrameName(TYPE_TO_CHARA_SPRITE_FRAME_NAME.at(type)) };
    Size charaSize { chara->getContentSize() };
    Point charaPos { TYPE_TO_CHARA_POSITION.at(type) };
    chara->setPosition(charaSize.width / 2 + charaPos.x, charaSize.height / 2 + charaPos.y);
    this->addChild(chara);
    _chara = chara;
    
    // カーソル
    Light::Information lightInfo { Light::Information(Color3B::WHITE, 200, "light.png") };
    lightInfo.type = Light::Type::TORCH;
    Light* cursor { Light::create(lightInfo) };
    cursor->setBlendFunc(BlendFunc{GL_SRC_COLOR, GL_ONE});
    cursor->setPosition(TYPE_TO_CURSOR_POSITION.at(type));
    title->addChild(cursor);
    _cursor = cursor;
    
    chara->setOpacity(0);
    cursor->setOpacity(0);
    
    return true;
}

// 表示
void TitleSelectPanel::show(function<void()> callback)
{
    this->stopAllActions();
    this->runAction(TargetedAction::create(_chara, FadeIn::create(0.4f)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.4f), CallFunc::create(callback)));
}

// フォーカスされた時
void TitleSelectPanel::onFocused(function<void()> callback)
{
    this->stopAllActions();
    _chara->setGlobalZOrder(FOCUSED_CHARA_Z_ORDER);
    this->runAction(TargetedAction::create(_chara, TintTo::create(0.2f, 255, 255, 255)));
    this->runAction(TargetedAction::create(_cursor, FadeIn::create(0.2f)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.2f), CallFunc::create(callback)));
}

// フォーカスはずされた時
void TitleSelectPanel::onUnFocused(function<void()> callback)
{
    this->stopAllActions();
    _chara->setGlobalZOrder(UNFOCUSED_CHARA_Z_ORDER);
    this->runAction(TargetedAction::create(_chara, TintTo::create(0.2f, 70, 70, 70)));
    this->runAction(TargetedAction::create(_cursor, FadeOut::create(0.2f)));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.2f), CallFunc::create(callback)));
}
