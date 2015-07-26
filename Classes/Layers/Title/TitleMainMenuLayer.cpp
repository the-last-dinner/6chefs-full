//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "TitleMainMenuLayer.h"

const map<string, TitleMainMenuLayer::MenuType> TitleMainMenuLayer::menu = {
	{"はじめから", TitleMainMenuLayer::MenuType::START},
	{"つづきから", TitleMainMenuLayer::MenuType::CONTINUE},
	{"終了", TitleMainMenuLayer::MenuType::START}
};

// コンストラクタ
TitleMainMenuLayer::TitleMainMenuLayer()
{FUNCLOG}

// デストラクタ
TitleMainMenuLayer::~TitleMainMenuLayer()
{FUNCLOG}

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
	int i = 0;
	for(map<string, MenuType>::const_iterator it = menu.begin(); it != menu.end(); it++)
	{
		Label* menu = Label::createWithSystemFont(it->first, "Arial", menuSize);
		menu->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - (menuSize + 20) * i);
		menu->setTextColor(Color4B::RED);
		menu->setOpacity(0);
		this->addChild(menu);
		baseMenuLayer::menuObjects.push_back(menu);
		
		menu->runAction(Sequence::create(DelayTime::create(1.f * i),
										 Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
										 nullptr));
		i++;
	}
	
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(2.f)),
									 CallFunc::create([this](){baseMenuLayer::eventListener->setEnabled(true);this->moveCursor(false);}),
									 nullptr));

	return true;
}

// カーソルを移動
void TitleMainMenuLayer::moveCursor(bool sound)
{
	FUNCLOG
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
	FUNCLOG
	switch (static_cast<MenuType>(baseMenuLayer::getSelectedIndex())) {
		case MenuType::START:
			SoundManager::getInstance()->playSound("se/gameStart.mp3");
			SoundManager::getInstance()->unloadAllSounds();
			TextureManager::getInstance()->unloadAllTectures();
			Director::getInstance()->replaceScene(DungeonScene::createScene());
			break;
		case MenuType::CONTINUE:
			
			break;
		case MenuType::FINISH:
			SoundManager::getInstance()->playSound("se/back.mp3");
			Director::getInstance()->end();
			break;
		default:
			break;
	}
	return;
}
