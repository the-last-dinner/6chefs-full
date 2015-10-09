//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "Layers/Menu/TitleMainMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

const map<TitleMainMenuLayer::MenuType, string> TitleMainMenuLayer::menu = {
	{TitleMainMenuLayer::MenuType::START, string("はじめから")},
	{TitleMainMenuLayer::MenuType::CONTINUE, string("つづきから")},
	{TitleMainMenuLayer::MenuType::EXIT, string("終了")},
};

// コンストラクタ
TitleMainMenuLayer::TitleMainMenuLayer(){FUNCLOG}

// デストラクタ
TitleMainMenuLayer::~TitleMainMenuLayer(){FUNCLOG}

// 初期化
bool TitleMainMenuLayer::init()
{
	FUNCLOG
	if(!MenuLayer::init(1, menu.size())) return false;
	
	//タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("title.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
	
	int menuSize = 32;
	for(int i = 0; i < static_cast<int>(MenuType::SIZE); i++)
	{
		Label* menu = Label::createWithTTF(this->menu.at(static_cast<MenuType>(i)), "fonts/cinecaption2.28.ttf", menuSize);
		menu->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - (menuSize + 20) * i);
		menu->setTextColor(Color4B::RED);
		menu->setOpacity(0);
		this->addChild(menu);
		MenuLayer::menuObjects.push_back(menu);
		
		menu->runAction(Sequence::create(DelayTime::create(1.f * i),
										 Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
										 nullptr));
	}
	
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(2.f)),
									 CallFunc::create([this](){this->listenerKeyboard->setEnabled(true);this->onIndexChanged(this->getSelectedIndex(), false);}),
									 nullptr));

	return true;
}

// 表示
void TitleMainMenuLayer::show()
{
	this->listenerKeyboard->setEnabled(true);
}

// 非表示
void TitleMainMenuLayer::hide()
{
	this->listenerKeyboard->setEnabled(false);
}

// 選択しているindexが変わった時
void TitleMainMenuLayer::onIndexChanged(int newIdx, bool sound)
{
	for(int i = 0; i < MenuLayer::menuObjects.size(); i++)
	{
        Node* obj {this->menuObjects.at(i)};
		this->runAction(Spawn::create(TargetedAction::create(obj, ScaleTo::create(0.2f, (newIdx == i)?1.2f:1.f)),
									  TargetedAction::create(obj, TintTo::create(0.5f, 255, 255, 255)),
									  nullptr));
	}
	if(sound)SoundManager::getInstance()->playSound("se/cursorMove.mp3");
	return;
}

// 決定キーを押した時
void TitleMainMenuLayer::onSpacePressed(int idx)
{
	map<MenuType, function<void()>> typeMap
	{
		{MenuType::START, this->onStartSelected},
		{MenuType::CONTINUE, this->onContinueSelected},
		{MenuType::EXIT, this->onExitSelected},
	};
	
	if(!typeMap.count(static_cast<MenuType>(idx))) return;
	
	if(function<void()> callback {typeMap.at(static_cast<MenuType>(idx))}) callback();
}
