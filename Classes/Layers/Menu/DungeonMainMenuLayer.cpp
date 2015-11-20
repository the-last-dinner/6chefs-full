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
#include "Datas/MapObject/CharacterData.h"

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
	hBg->setCascadeOpacityEnabled(true);
	this->addChild(hBg);
    
    // チャプター表示
    int chapter_id = PlayerDataManager::getInstance()->getChapterId();
    Label* chapter_name = Label::createWithTTF(CsvDataManager::getInstance()->getChapterName(chapter_id), "fonts/cinecaption2.28.ttf", 30);
    chapter_name->setPosition(chapter_name->getContentSize().width / 2 + 15, WINDOW_HEIGHT - hBg->getContentSize().height - chapter_name->getContentSize().height / 2 - 15);
    cover->addChild(chapter_name);
    
    Label* chapter_title = Label::createWithTTF(CsvDataManager::getInstance()->getChapterTitle(chapter_id), "fonts/cinecaption2.28.ttf", 30);
    chapter_title->setPosition(chapter_title->getContentSize().width / 2 + 45, WINDOW_HEIGHT - hBg->getContentSize().height - chapter_name->getContentSize().height - chapter_title->getContentSize().height / 2 - 30);
    cover->addChild(chapter_title);
    
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
        menu->setTag(i);
        hBg->addChild(menu);
        this->menuObjects.push_back(menu);
    }
    
    // マップ名表示
    Label* mapName = Label::createWithTTF(CsvDataManager::getInstance()->getMapName(PlayerDataManager::getInstance()->getLocation().map_id), "fonts/cinecaption2.28.ttf", 26);
    mapName->setPosition(mapName->getContentSize().width / 2 + 15, hBg->getContentSize().height - mapName->getContentSize().height / 2 - 15);
    hBg->addChild(mapName);
    
    Label* play_time = Label::createWithTTF(PlayerDataManager::getInstance()->getPlayTimeDisplay(), "fonts/cinecaption2.28.ttf", 26);
    play_time->setPosition(hBg->getContentSize().width - play_time->getContentSize().width/2 - 15, hBg->getContentSize().height - play_time->getContentSize().height / 2 - 15);
    hBg->addChild(play_time);
    
	// 下のメニューを生成
    Sprite* fBg { Sprite::create() };
	fBg->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	fBg->setColor(Color3B::GRAY);
	fBg->setPosition(fBg->getContentSize().width / 2, fBg->getContentSize().height / 2);
	//fBg->setOpacity(0);
	fBg->setCascadeOpacityEnabled(true);
	this->addChild(fBg);
    
    // 装備品表示
    int right_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::RIGHT);
    int left_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::LEFT);
    string right = (right_id != 0) ? CsvDataManager::getInstance()->getItemName(right_id) : "なし";
    string left = (left_id != 0) ? CsvDataManager::getInstance()->getItemName(left_id) : "なし";
    Label* equipment = Label::createWithTTF("装備\n右手 : " + right + "\n左手 : " + left, "fonts/cinecaption2.28.ttf", 26);
    equipment->setPosition(equipment->getContentSize().width / 2 + 15, fBg->getContentSize().height - equipment->getContentSize().height / 2 - 15);
    fBg->addChild(equipment);
    
    // キャラ表示
    vector<CharacterData> charas = PlayerDataManager::getInstance()->getPartyMemberAll();
    int party_count = charas.size();
    Size  cPanelSize = Size(fBg->getContentSize().width/5, fBg->getContentSize().height);
    float stand_scale = 0.25;
    for (int i = 0; i < party_count; i++)
    {
        float colum_position = cPanelSize.width * (5 - party_count + i) + cPanelSize.width / 2;
        // キャラ毎にパネルを作成
        Sprite* chara_panel {Sprite::create()};
        chara_panel->setTextureRect(Rect(0,0, cPanelSize.width, cPanelSize.height));
        chara_panel->setPosition(colum_position, cPanelSize.height / 2);
        //chara_panel->setColor(Color3B::RED);
        chara_panel->setOpacity(0);
        fBg->addChild(chara_panel);
        
        // 通り名
        Label* street= Label::createWithTTF("-" + CsvDataManager::getInstance()->getCharaStreetName(charas[i].chara_id) + "-", "fonts/cinecaption2.28.ttf", 24);
        street->setPosition(cPanelSize.width / 2, cPanelSize.height - street->getContentSize().height / 2 - 5);
        chara_panel->addChild(street);
        
        // キャラ名
        Label* name = Label::createWithTTF(CsvDataManager::getInstance()->getCharaName(charas[i].chara_id), "fonts/cinecaption2.28.ttf", 24);
        name->setPosition(cPanelSize.width / 2, cPanelSize.height - street->getContentSize().height - name->getContentSize().height /2 - 15);
        chara_panel->addChild(name);
        
        // キャラのドット絵
        string file_name = charas[i].getDotFileName();
        if (SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name))
        {
            Sprite* dotimg {Sprite::createWithSpriteFrameName(file_name)};
            dotimg->setPosition(cPanelSize.width / 2, dotimg->getContentSize().height / 2 + 5);
            dotimg->setZOrder(1);
            chara_panel->addChild(dotimg);
        }
        
        // キャラの立ち絵
        file_name = charas[i].getStandFileName();
        if(SpriteFrameCache::getInstance()->getSpriteFrameByName(file_name))
        {
            Sprite* img { Sprite::createWithSpriteFrameName(file_name)};
            img->setScale(stand_scale);
            img->setPosition(colum_position, img->getContentSize().height * stand_scale / 2 + fBg->getContentSize().height);
            img->setLocalZOrder(-1);
            cover->addChild(img);
        }
        
    }
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
    // カーソル処理
    for(Node* obj : this->menuObjects)
    {
        if(obj->getTag() == newIdx)
        {
            obj->runAction(FadeTo::create(0.1f, 255));
            obj->runAction(ScaleTo::create(0.2f, 1.2f));
        }
        else
        {
            obj->runAction(FadeTo::create(0.1f, 128));
            obj->runAction(ScaleTo::create(0.2f, 1.0f));
        }
        obj->runAction(TintTo::create(0.5f, 255, 255, 255));
    }
    if(sound)SoundManager::getInstance()->playSE("cursorMove.mp3");
    return;
}

// 決定キー入力時
void DungeonMainMenuLayer::onSpacePressed(int idx)
{
    SoundManager::getInstance()->playSE("cursorMove.mp3");
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
            SoundManager::getInstance()->playSE("back.mp3");
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