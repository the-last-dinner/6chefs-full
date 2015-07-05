//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "TitleMainMenuLayer.h"

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
	if(!baseMenuLayer::init(CC_CALLBACK_1(TitleMainMenuLayer::moveCursor, this), CC_CALLBACK_0(TitleMainMenuLayer::onSpacePressed, this))) return false;
	
	// メニューを生成
	baseMenuLayer::menuStrings =
	{
		"はじめから",
		"終了",
	};
	baseMenuLayer::sizeX = 1;
	baseMenuLayer::sizeY = baseMenuLayer::menuStrings.size();
	
	//タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("title.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
	
	int menuSize = 32;
	for(int i = 0; i < baseMenuLayer::menuStrings.size(); i++)
	{
		Label* menu = Label::createWithSystemFont(baseMenuLayer::menuStrings.at(i), "Arial", menuSize);
		menu->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - (menuSize + 20) * i);
		menu->setTag(i);
		menu->setTextColor(Color4B::RED);
		menu->setOpacity(0);
		this->addChild(menu);
		
		menu->runAction(Sequence::create(DelayTime::create(1.f * i),
										 Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
										 nullptr));
	}
	
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(2.f)),
									 CallFunc::create([this](){this->eventListener->setEnabled(true);this->moveCursor(false);}),
									 nullptr));

	return true;
}

// カーソルを移動
void TitleMainMenuLayer::moveCursor(bool sound)
{
	FUNCLOG
	for(int i = 0; i < menuStrings.size(); i++)
	{
		Node* menu = this->getChildByTag(i);
		this->runAction(Spawn::create(TargetedAction::create(menu, ScaleTo::create(0.2f, (indexY == i)?1.1f:1.f)),
									  TargetedAction::create(menu, TintTo::create(0.5f, 255, 255, 255)),
									  nullptr));
	}
	if(sound)SoundManager::getInstance()->playSound("se/cursorMove.mp3");
	return;
}

// 決定キーを押した時
void TitleMainMenuLayer::onSpacePressed()
{
	FUNCLOG
	switch (indexY) {
		case 0:
			SoundManager::getInstance()->playSound("se/gameStart.mp3");
			Director::getInstance()->replaceScene(DungeonScene::createScene());
			break;
		case 1:
			SoundManager::getInstance()->playSound("se/back.mp3");
			Director::getInstance()->end();
			break;
		default:
			break;
	}
	return;
}
