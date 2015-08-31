//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "Layers/Title/TitleMainMenuLayer.h"

#include "Scenes/DungeonScene.h"

#include "Layers/SaveData/SaveDataSelector.h"

const map<TitleMainMenuLayer::MenuType, string> TitleMainMenuLayer::menu = {
	{TitleMainMenuLayer::MenuType::START, "はじめから"},
	{TitleMainMenuLayer::MenuType::CONTINUE, "つづきから"},
	{TitleMainMenuLayer::MenuType::EXIT, "終了"},
};

// コンストラクタ
TitleMainMenuLayer::TitleMainMenuLayer(){FUNCLOG}

// デストラクタ
TitleMainMenuLayer::~TitleMainMenuLayer(){FUNCLOG}

// 初期化
bool TitleMainMenuLayer::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	if(!baseMenuLayer::init(1, menu.size())) return false;
	
	//タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("title.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
	
	int menuSize = 32;
	for(int i = 0; i < static_cast<int>(MenuType::SIZE); i++)
	{
		Label* menu = Label::createWithSystemFont(this->menu.at(static_cast<MenuType>(i)), "fonts/cinecaption2.28.ttf", menuSize);
		menu->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - (menuSize + 20) * i);
		menu->setTextColor(Color4B::RED);
		menu->setOpacity(0);
		this->addChild(menu);
		baseMenuLayer::menuObjects.push_back(menu);
		
		menu->runAction(Sequence::create(DelayTime::create(1.f * i),
										 Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
										 nullptr));
	}
	
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(2.f)),
									 CallFunc::create([this](){baseMenuLayer::eventListener->setEnabled(true);this->onIndexChanged(false);}),
									 nullptr));

	return true;
}

// 表示
void TitleMainMenuLayer::show()
{
	this->eventListener->setEnabled(true);
}

// 非表示
void TitleMainMenuLayer::hide()
{
	this->eventListener->setEnabled(false);
}

// 選択しているindexが変わった時
void TitleMainMenuLayer::onIndexChanged(bool sound)
{
	int selectedIndex = baseMenuLayer::getSelectedIndex();
	for(int i = 0; i < baseMenuLayer::menuObjects.size(); i++)
	{
		Node* obj = baseMenuLayer::menuObjects.at(i);
		this->runAction(Spawn::create(TargetedAction::create(obj, ScaleTo::create(0.2f, (selectedIndex == i)?1.2f:1.f)),
									  TargetedAction::create(obj, TintTo::create(0.5f, 255, 255, 255)),
									  nullptr));
	}
	if(sound)SoundManager::getInstance()->playSound("se/cursorMove.mp3");
	return;
}

// 決定キーを押した時
void TitleMainMenuLayer::onSpacePressed()
{
	switch (static_cast<MenuType>(baseMenuLayer::getSelectedIndex())) {
		case MenuType::START:
			if(this->onStartSelected)
			{
				this->onStartSelected();
			}
			break;
			
		case MenuType::CONTINUE:
			if(this->onContinueSelected)
			{
				this->onContinueSelected();
			}
			break;
			
		case MenuType::EXIT:
			if(this->onExitSelected)
			{
				this->onExitSelected();
			}
			break;
			
		default:
			break;
	}
}
