//
//  TitleSelectMenuLayer.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#include "Layers/TitleSelect/TitleSelectMenuLayer.h"

#include "Layers/TitleSelect/TitleSelectPanel.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Managers/ResourcesManager.h"

// コンストラクタ
TitleSelectMenuLayer::TitleSelectMenuLayer() { FUNCLOG }

// デストラクタ
TitleSelectMenuLayer::~TitleSelectMenuLayer() { FUNCLOG }

// 初期化
bool TitleSelectMenuLayer::init(function<void(int)> onSelectTitle)
{
    if (!MenuLayer::init(2, 1)) return false;
    _onSelectTitle = onSelectTitle;
    
    // 背景
    Sprite* bg { Sprite::createWithSpriteFrameName("title_select_bg.png") };
    Size bgSize { bg->getContentSize() };
    bg->setPosition(bgSize.width / 2, bgSize.height / 2);
    this->addChild(bg);
    _bg = bg;
    
    TitleSelectPanel* panel2 { TitleSelectPanel::create(TitleSelectPanel::TYPE::TWO) };
    this->addChild(panel2);
    
    TitleSelectPanel* panel1 { TitleSelectPanel::create(TitleSelectPanel::TYPE::ONE) };
    this->addChild(panel1);
    
    _panels.push_back(panel1);
    _panels.push_back(panel2);
    
    this->menuObjects.push_back(panel1);
    this->menuObjects.push_back(panel2);
    
    bg->setOpacity(0);
    
    return true;
}

// 表示
void TitleSelectMenuLayer::show()
{
    _bg->runAction(FadeIn::create(0.2f));
    _panels[0]->runAction(Sequence::createWithTwoActions(DelayTime::create(0.2f), CallFunc::create([this](){ _panels[0]->show(); })));
    _panels[1]->runAction(Sequence::createWithTwoActions(DelayTime::create(0.4f), CallFunc::create([this](){ _panels[1]->show(); })));
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.8f), CallFunc::create(CC_CALLBACK_0(TitleSelectMenuLayer::onShowAnimationFinished, this))));
    this->setSelectTitleLabel();
}

// 非表示
void TitleSelectMenuLayer::hide()
{

}

// インデックスが変わった時
// カーソルを移動させたりする
void TitleSelectMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    // パネルのフォーカス変更
    for (int idx {0}; idx < _panels.size(); idx++) {
        TitleSelectPanel* panel { _panels[idx] };
        if (idx == newIdx) {
            panel->onFocused();
        } else {
            panel->onUnFocused();
        }
    }
    
    // Labelの色変更
    if (newIdx == 0) {
        _selectTitleLabel->setColor(Color3B::BLACK);
    } else {
        _selectTitleLabel->setColor(Color3B::WHITE);
    }
    
    // 移動音
    if (sound) SoundManager::getInstance()->playSE(Resource::SE::CURSOR_MOVE);
}

// 決定キー押した時
void TitleSelectMenuLayer::onEnterKeyPressed(int idx)
{
    if (_onSelectTitle) _onSelectTitle(idx);
}

// 表示アニメーション終了時
void TitleSelectMenuLayer::onShowAnimationFinished()
{
    this->listenerKeyboard->setEnabled(true);
    this->onIndexChanged(0, false);
}

// SELECT_TITLE_LABELをセット
void TitleSelectMenuLayer::setSelectTitleLabel()
{
    Label* selectTitleLabel {Label::createWithTTF("←→ SELECT TITLE", Resource::Font::MESSAGE, 20)};
    selectTitleLabel->setPosition(Point(WINDOW_WIDTH/2, selectTitleLabel->getContentSize().height * 2));
    selectTitleLabel->setColor(Color3B::BLACK);
    selectTitleLabel->setOpacity(200);
    selectTitleLabel->setGlobalZOrder(1000);
    this->addChild(selectTitleLabel);
    
    _selectTitleLabel = selectTitleLabel;
    
    // 点滅を設定
//    ActionInterval* flashing = Sequence::createWithTwoActions(
//          TargetedAction::create(selectTitleLabel, FadeTo::create(0.6f, 200)),
//          TargetedAction::create(selectTitleLabel, FadeTo::create(0.6f, 30))
//    );
//    this->runAction(RepeatForever::create(flashing));
}
