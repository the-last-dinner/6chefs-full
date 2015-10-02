//
//  DungeonMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/09/06.
//
//

#include "Layers/Menu/DungeonMainMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// コンストラクタ
DungeonMainMenuLayer::DungeonMainMenuLayer(){FUNCLOG}

// デストラクタ
DungeonMainMenuLayer::~DungeonMainMenuLayer(){FUNCLOG}

// 初期化
bool DungeonMainMenuLayer::init()
{
	FUNCLOG
	if(!MenuLayer::init(static_cast<int>(Type::SIZE), 1)) return false;
	
	// 半透明の黒幕を生成
	Sprite* cover { Sprite::create() };
	cover->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	cover->setColor(Color3B::BLACK);
	cover->setPosition(WINDOW_CENTER);
	cover->setOpacity(100);
	this->addChild(cover);
	
	// 上のメニューを生成
	Sprite* hBg { Sprite::create() };
	hBg->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	hBg->setColor(Color3B::GRAY);
	hBg->setPosition(hBg->getContentSize().width / 2, WINDOW_HEIGHT - hBg->getContentSize().height / 2);
	//hBg->setOpacity(0);
	hBg->setCascadeOpacityEnabled(true);
	this->addChild(hBg);
    
	// 下のメニューを生成
    Sprite* fBg { Sprite::create() };
	fBg->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	fBg->setColor(Color3B::GRAY);
	fBg->setPosition(fBg->getContentSize().width / 2, fBg->getContentSize().height / 2);
	//fBg->setOpacity(0);
	fBg->setCascadeOpacityEnabled(true);
	this->addChild(fBg);
	
	// メニューの選択肢を生成
	map<Type, string> menuStrings
	{
		{Type::ITEM, "アイテム"},
		{Type::SAVE, "セーブ"},
		{Type::CHARA, "キャラ"},
		{Type::TITLE, "タイトル"},
		{Type::CLOSE, "閉じる"},
	};
	for(int i {0}; i < static_cast<int>(Type::SIZE); i++)
	{
		Label* menu = Label::createWithTTF(menuStrings.at(static_cast<Type>(i)), "fonts/cinecaption2.28.ttf", 26);
		menu->setPosition((WINDOW_WIDTH / static_cast<int>(Type::SIZE)) * (i + 0.5), 40);
		hBg->addChild(menu);
		this->menuObjects.push_back(menu);
	}
	
	// マップ名表示
    Label* mapName = Label::createWithTTF(CsvDataManager::getInstance()->getDisplayName(CsvDataManager::DataType::MAP, PlayerDataManager::getInstance()->getLocation().map_id), "fonts/cinecaption2.28.ttf", 26);
	mapName->setPosition(mapName->getContentSize().width / 2, hBg->getContentSize().height - mapName->getContentSize().height / 2);
	hBg->addChild(mapName);
	
	return true;
}

// メニュー表示
void DungeonMainMenuLayer::show()
{
	FUNCLOG
    this->setVisible(true);
    this->listenerKeyboard->setEnabled(true);
}

// メニューを非表示
void DungeonMainMenuLayer::hide()
{
	FUNCLOG
    this->setVisible(false);
    this->listenerKeyboard->setEnabled(false);
}

// カーソル移動時
void DungeonMainMenuLayer::onIndexChanged(int newIdx, bool sound)
{

}

// 決定キー入力時
void DungeonMainMenuLayer::onSpacePressed(int idx)
{
    
}

//　メニューキー入力時
void DungeonMainMenuLayer::onMenuKeyPressed()
{
    this->hide();
}