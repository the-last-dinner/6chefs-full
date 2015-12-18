//
//  TitleMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "Layers/Menu/TitleMainMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "UI/Cloud.h"

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
        {MenuType::TROPHY, "トロフィ"},
        //{MenuType::EXIT, "終了"},
    };
    
	if(!MenuLayer::init(1, typeToString.size())) return false;
	
	// タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("background.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
    
    // タイトル文字を生成
    float font_size = 56.f;
    
    Label* title1 {Label::createWithTTF("6人の料理人", Resource::Font::SYSTEM, font_size)};
    title1->setPosition(WINDOW_WIDTH/2, WINDOW_HEIGHT - title1->getContentSize().height * 2);
    title1->setColor(Color3B::Color3B(200,0,0));
    title1->setOpacity(0);
    this->addChild(title1);
    
    Label* title2 {Label::createWithTTF("と", Resource::Font::SYSTEM, font_size)};
    title2->setPosition(WINDOW_WIDTH/2, title1->getPosition().y - title2->getContentSize().height);
    title2->setOpacity(0);
    title2->setColor(Color3B::WHITE);
    this->addChild(title2);
    
    Label* title3 {Label::createWithTTF("隻眼の少女", Resource::Font::SYSTEM, font_size)};
    title3->setPosition(WINDOW_WIDTH/2, title2->getPosition().y - title3->getContentSize().height);
    title3->setColor(Color3B::Color3B(200,0,0));
    title3->setOpacity(0);
    this->addChild(title3);
    
    // タイトルメニューを生成
	int menuSize = 48.f;
	for(int i = 0; i < static_cast<int>(MenuType::SIZE); i++)
	{
        Label* menuItem { Label::createWithTTF(typeToString[static_cast<MenuType>(i)], Resource::Font::SYSTEM, menuSize) };
		menuItem->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5 / 11 - (menuSize + 20) * i);
		menuItem->setOpacity(0);
		this->addChild(menuItem);
		this->menuObjects.push_back(menuItem);
		
		menuItem->runAction(Sequence::create(DelayTime::create(1.f * i),
                                             Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
                                             nullptr));
	}
    
    // カーソル生成
    Cloud* cursor { Cloud::create(Size::ZERO) };
    cursor->setColor(Color3B(100, 0, 0));
    cursor->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
    this->addChild(cursor);
    this->cursor = cursor;
	
    this->runAction(Sequence::create(
                                     TargetedAction::create(title1, FadeIn::create(1.f)),
                                     TargetedAction::create(title2,FadeTo::create(1.f, 200)),
                                     TargetedAction::create(title3,FadeIn::create(1.f)),
                                    nullptr
                    ));
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(1.f)),
									 CallFunc::create([this](){this->listenerKeyboard->setEnabled(true);this->onIndexChanged(this->getSelectedIndex(), false);}),
									 nullptr));
    
    // クリア時の立ち絵
    float scale = 0.3f;
    if (PlayerDataManager::getInstance()->getGlobalData()->getClearCount() > 0)
    {
        Sprite* left {Sprite::createWithSpriteFrameName("yuki_s_1.png")};
        left->setScale(scale);
        left->setOpacity(0);
        left->setPosition(left->getContentSize().width * scale / 2, left->getContentSize().height * scale / 2);
        this->addChild(left);
        left->runAction(Sequence::createWithTwoActions(DelayTime::create(2.f), FadeTo::create(2.f, 128)));
    }
    
    // トゥルーエンドを見た場合
    if (PlayerDataManager::getInstance()->getGlobalData()->hasTrophy(8))
    {
        Sprite* right {Sprite::createWithSpriteFrameName("magoichi_s_1.png")};
        right->setScale(scale);
        right->setOpacity(0);
        right->setPosition(WINDOW_WIDTH - right->getContentSize().width * scale / 2, right->getContentSize().height * scale / 2);
        this->addChild(right);
        right->runAction(Sequence::createWithTwoActions(DelayTime::create(4.f), FadeTo::create(2.f, 128)));
    }
    
    // 操作方法
    Label* opr {Label::createWithTTF("SPACE:決定 X:戻る", Resource::Font::MESSAGE, 18)};
    opr->setPosition(WINDOW_WIDTH/2, opr->getContentSize().height);
    opr->setColor(Color3B::WHITE);
    opr->setOpacity(0);
    this->addChild(opr);
    opr->runAction(FadeTo::create(1.2f, 200));
    
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
        if (newIdx != i) continue;
        
        Node* obj {this->menuObjects.at(i)};
        this->cursor->setScale((obj->getContentSize().width + 50) / this->cursor->getContentSize().width);
        this->cursor->setPosition(obj->getPosition());
	}
    if(sound)SoundManager::getInstance()->playSE(Resource::SE::CURSOR_MOVE);
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
