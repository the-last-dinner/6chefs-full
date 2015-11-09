//
//  DungeonMainMenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/09/06.
//
//

#include "Layers/Menu/DungeonMainMenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Scenes/TitleScene.h"

// コンストラクタ
DungeonMainMenuLayer::DungeonMainMenuLayer(){FUNCLOG}

// デストラクタ
DungeonMainMenuLayer::~DungeonMainMenuLayer(){FUNCLOG}

// 初期化
bool DungeonMainMenuLayer::init()
{
	FUNCLOG
	if(!MenuLayer::init(static_cast<int>(Type::SIZE), 1)) return false;
	
    //半透明の黒幕を生成
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
		{ Type::SAVE, "セーブ" },
		{ Type::CHARA, "キャラ" },
		{ Type::TITLE, "タイトル" },
		{ Type::CLOSE, "閉じる" },
	};
	
	for(int i {0}; i < static_cast<int>(Type::SIZE); i++)
	{
		Label* menu = Label::createWithTTF(menuStrings.at(static_cast<Type>(i)), "fonts/cinecaption2.28.ttf", 26);
		menu->setPosition((WINDOW_WIDTH / static_cast<int>(Type::SIZE)) * (i + 0.5), 40);
		hBg->addChild(menu);
		this->menuObjects.push_back(menu);
	}
	
	// マップ名表示
    Label* mapName = Label::createWithTTF(CsvDataManager::getInstance()->getMapName(PlayerDataManager::getInstance()->getLocation().map_id), "fonts/cinecaption2.28.ttf", 26);
	mapName->setPosition(mapName->getContentSize().width / 2, hBg->getContentSize().height - mapName->getContentSize().height / 2);
	hBg->addChild(mapName);
    
    // 装備品表示
    int right_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::RIGHT);
    int left_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::LEFT);
    string right = (right_id != 0) ? CsvDataManager::getInstance()->getItemName(right_id) : "なし";
    string left = (left_id != 0) ? CsvDataManager::getInstance()->getItemName(left_id) : "なし";
    Label* equipment = Label::createWithTTF("装備\n右手 : " + right + "\n左手 : " + left, "fonts/cinecaption2.28.ttf", 26);
    equipment->setPosition(equipment->getContentSize().width / 2, fBg->getContentSize().height - equipment->getContentSize().height / 2);
    fBg->addChild(equipment);
    
    // キャラ表示
    Label* chara = Label::createWithTTF("-カレー屋-\n佐々木孫一", "fonts/cinecaption2.28.ttf", 26);
    chara->setPosition(-25 + fBg->getContentSize().width - chara->getContentSize().width / 2, fBg->getContentSize().height - chara->getContentSize().height / 2);
    fBg->addChild(chara);
	return true;
}

// メニュー表示
void DungeonMainMenuLayer::show()
{
	FUNCLOG
    this->onIndexChanged(this->menuIndex);
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
    this->menuIndex = newIdx;
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

// 決定キー入力時
void DungeonMainMenuLayer::onSpacePressed(int idx)
{
    SoundManager::getInstance()->playSound("se/cursorMove.mp3");
    switch (static_cast<Type>(idx)) {
        case Type::ITEM:
            if (this->onItemMenuSelected)
            {
                this->onItemMenuSelected();
            }
            this->onItemMenuSelected();
            break;
        case Type::SAVE:
            if (this->onSaveMenuSelected)
            {
                this->onSaveMenuSelected();
            }
            break;
        case Type::CHARA:
            if (this->onCharacterMenuSelected)
            {
                this->onCharacterMenuSelected();
            }
            break;
        case Type::TITLE:
            SoundManager::getInstance()->playSound("se/back.mp3");
            Director::getInstance()->replaceScene(TitleScene::create());
            break;
        case Type::CLOSE:
        default:
            this->onMenuKeyPressed();
            break;
    }
}

//　メニューキー入力時
void DungeonMainMenuLayer::onMenuKeyPressed()
{
    this->hide();
    if(this->onMenuHidden)
    {
        this->onMenuHidden();
    }
}

// 選択されているメニュー番号を取得
int DungeonMainMenuLayer::getMenuIndex(){
    return this->getMenuIndex();
}