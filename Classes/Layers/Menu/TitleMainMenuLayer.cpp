//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "Layers/Menu/TitleMainMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// コンストラクタ
TitleMainMenuLayer::TitleMainMenuLayer(){FUNCLOG}

// デストラクタ
TitleMainMenuLayer::~TitleMainMenuLayer(){FUNCLOG}

// 初期化
bool TitleMainMenuLayer::init()
{
    map<MenuType, string> typeToString
    {
        {MenuType::START, "はじめから"},
        {MenuType::CONTINUE, "つづきから"},
        {MenuType::TROPHY, "トロフィー"},
        {MenuType::EXIT, "終了"},
    };
    
	if(!MenuLayer::init(1, typeToString.size())) return false;
	
	//タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("title.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
	
	int menuSize = 50;
	for(int i = 0; i < static_cast<int>(MenuType::SIZE); i++)
	{
        Label* menuItem { Label::createWithTTF(typeToString[static_cast<MenuType>(i)], Resource::Font::SYSTEM, menuSize) };
		menuItem->setPosition(WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 3 / 4 - (menuSize + 20) * i);
		menuItem->setColor(Color3B::RED);
		menuItem->setOpacity(0);
		this->addChild(menuItem);
		this->menuObjects.push_back(menuItem);
		
		menuItem->runAction(Sequence::create(DelayTime::create(1.f * i),
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
        if (newIdx == i)
        {
            obj->runAction(ScaleTo::create(0.2f, 1.2f));
            obj->runAction(TintTo::create(0.2f, 255, 255, 255));
        }
        else
        {
            obj->runAction(ScaleTo::create(0.2f, 1.f));
            obj->runAction(TintTo::create(0.2f, Color3B::RED));
        }
	}
	if(sound)SoundManager::getInstance()->playSE("cursorMove.mp3");
	return;
}

// 決定キーを押した時
void TitleMainMenuLayer::onSpacePressed(int idx)
{
	map<MenuType, function<void()>> typeMap
	{
		{MenuType::START, this->onStartSelected},
		{MenuType::CONTINUE, this->onContinueSelected},
        {MenuType::TROPHY, this->onTrophySelected},
		{MenuType::EXIT, this->onExitSelected},
	};
	
	if(!typeMap.count(static_cast<MenuType>(idx))) return;
	
	if(function<void()> callback {typeMap.at(static_cast<MenuType>(idx))}) callback();
}
