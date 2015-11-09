//
//  ItemMenuLayer.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/01.
//
//

#include "Layers/Menu/ItemMenuLayer.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"
#include "Scenes/DungeonScene.h"
#include "Layers/Menu/MiniSelector.h"

// コンストラクタ
ItemMenuLayer::ItemMenuLayer(){FUNCLOG}

// デストラクタ
ItemMenuLayer::~ItemMenuLayer(){FUNCLOG}

// ItemMenuLayer生成
bool ItemMenuLayer::init()
{
    FUNCLOG
    int obj_count = PlayerDataManager::getInstance()->getItemAll().size();
    Point maxSize = Point(3,8);
    int sizeX = obj_count < maxSize.x ? obj_count : maxSize.x;
    int sizeY = obj_count < 16 ? floor((obj_count - 1 )/ 3) + 1 : maxSize.y;
    if (!MenuLayer::init(sizeX, sizeY)) return false;
    
    SpriteUtils::Square square;
    SpriteUtils::Margin margin;
    
    // 白い背景を生成
    Sprite* white = Sprite::create();
    white->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    white->setColor(Color3B::WHITE);
    white->setPosition(WINDOW_CENTER);
    //white->setOpacity(128);
    this->addChild(white);
    
    // タイトル
    square = SpriteUtils::Square(0,80,30,100);
    margin = SpriteUtils::Margin(3.0,1.5,1.5,3.0);
    Sprite* leftTop = SpriteUtils::getSquareSprite(square, margin);
    leftTop->setColor(Color3B(128,0,0));
    this->addChild(leftTop);
    
    Label* title = Label::createWithTTF("アイテム", "fonts/cinecaption2.28.ttf", 48);
    title->setPosition(leftTop->getContentSize().width / 2, leftTop->getContentSize().height / 2);
    title->setColor(Color3B::WHITE);
    leftTop->addChild(title);
    
    // アイテム詳細
    square = SpriteUtils::Square(0,0,100,25);
    margin = SpriteUtils::Margin(1.5,3.0,3.0,3.0);
    Sprite* bottom = SpriteUtils::getSquareSprite(square, margin);
    bottom->setColor(Color3B::BLACK);
    bottom->setName("bottom");
    this->addChild(bottom);
    
    // 装備
    square = SpriteUtils::Square(30,80,100,100);
    margin = SpriteUtils::Margin(3.0,3.0,1.5,1.5);
    Sprite* rightTop = SpriteUtils::getSquareSprite(square, margin);
    rightTop->setColor(Color3B::BLACK);
    this->addChild(rightTop);
    
    int right_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::RIGHT);
    int left_id = PlayerDataManager::getInstance()->getItemEquipment(Direction::LEFT);
    string right_equip = (right_id != 0) ? CsvDataManager::getInstance()->getItemName(right_id) : "なし";
    string left_equip = (left_id != 0) ? CsvDataManager::getInstance()->getItemName(left_id) : "なし";
    Label* equip_title = Label::createWithTTF("装備", "fonts/cinecaption2.28.ttf", 26);
    equip_title->setPosition(equip_title->getContentSize().width/2 + 30, rightTop->getContentSize().height - equip_title->getContentSize().height/2 - 10);
    equip_title->setColor(Color3B::WHITE);
    rightTop->addChild(equip_title);
    Label* equipment = Label::createWithTTF("右手 : " + right_equip + "\n左手 : " + left_equip, "fonts/cinecaption2.28.ttf", 26);
    equipment->setPosition(equipment->getContentSize().width/2 + 10, equipment->getContentSize().height/2 + 15);
    equipment->setColor(Color3B::WHITE);
    rightTop->addChild(equipment);
    
    // アイテムリスト
    square = SpriteUtils::Square(0,25,100,80);
    margin = SpriteUtils::Margin(1.5,3.0,1.5,3.0);
    Sprite* center = SpriteUtils::getSquareSprite(square, margin);
    center->setColor(Color3B::BLACK);
    this->addChild(center);
    
    map<int,int> items = PlayerDataManager::getInstance()->getItemAll();
    if (items.size() == 0){
        // アイテムが時は空用の番号をインサート
        items.insert({-1,0});
    }
    int i = 0;
    for(auto itr = items.begin(); itr != items.end(); itr++)
    {
        // パネル生成
        Sprite* panel = Sprite::create();
        Size list_size {center->getContentSize()};
        panel->setTextureRect(Rect(0, 0, list_size.width / maxSize.x, list_size.height / maxSize.y));
        panel->setColor(Color3B::BLACK);
        panel->setTag(i);
        Size panel_size {panel->getContentSize()};
        panel->setPosition((i%(int)maxSize.x) * (list_size.width / maxSize.x) + panel_size.width/2, list_size.height - ((floor(i/(int)maxSize.x) + 1)  *  (panel_size.height)) + panel_size.height/2);
        center->addChild(panel);
        // メニューオブジェクトに登録
        this->menuObjects.push_back(panel);
        // 不透明度を半分にしておく
        panel->setCascadeOpacityEnabled(true);
        panel->setOpacity(100);
        
        // アイテム
        this->items.push_back(itr->first);
        Label* item = Label::createWithTTF(CsvDataManager::getInstance()->getItemName(itr->first), "fonts/cinecaption2.28.ttf", 24);
        item->setPosition(panel_size.width/2 , panel_size.height / 2);
        item->setColor(Color3B::WHITE);
        panel->addChild(item);
        // インクリメント
        i++;
    }
    
    // デフォルトセレクト
    this->onIndexChanged(0, false);
    
    return true;
}

// アイテム説明部分生成
void ItemMenuLayer::changeItemDiscription(const int idx)
{
    // 親のスプライトを取得
    Node* bottom = this->getChildByName("bottom");
    // 子のスプライトがすでに存在すれば消してから生成
    string labelName = "discriptionLabel";
    if (bottom->getChildByName(labelName)){
        bottom->removeChildByName(labelName);
    }
    string str = LastSupper::StringUtils::strReplace("\\n", "\n", CsvDataManager::getInstance()->getItemDiscription(this->items[idx]));
    Label* discription = Label::createWithTTF(str, "fonts/cinecaption2.28.ttf", 24);
    //discription->setPosition(bottom->getContentSize().width / 2, leftBottom->getContentSize().height / 2);
    int margin = 10;
    discription->setPosition(discription->getContentSize().width / 2 + margin, bottom->getContentSize().height - discription->getContentSize().height / 2 - margin);
    discription->setColor(Color3B::WHITE);
    discription->setName(labelName);
    bottom->addChild(discription);
}

// 選択肢の生成
void ItemMenuLayer::createMiniSelector()
{
    // アイテムメニューのキーボードを無効化
    this->listenerKeyboard->setEnabled(false);
    // メニューラベル
    vector<string> labels;
    if (!PlayerDataManager::getInstance()->checkItemEquipment(this->selected_item))
    {
        labels = {"右手に装備", "左手に装備", "キャンセル"};
        this->isEquip = true;
    }
    else
    {
        labels = {"装備を外す", "キャンセル"};
        this->isEquip = false;
    }
    Point index = Point(1,labels.size()); // 要素数
    SpriteUtils::Square position = SpriteUtils::Square(76,80,100,100); // 位置
    MiniSelector::Selector selector = MiniSelector::Selector(index, position, labels);
    MiniSelector* mini = {MiniSelector::create(selector)};
    this->addChild(mini);
    mini->show();
    mini->onMiniSelectorCanceled = CC_CALLBACK_0(ItemMenuLayer::onMiniSelectorCanceled, this);
    mini->onMiniIndexSelected = CC_CALLBACK_1(ItemMenuLayer::onMiniIndexSelected, this);
    this->miniSelector = mini;
}

// ミニ選択肢が洗濯された時
void ItemMenuLayer::onMiniIndexSelected(const int idx)
{
    // 完了しましたがでている時
    if (this->miniSelector->confirm_flag)
    {
        this->onMiniSelectorCanceled();
        this->onItemMenuCanceled();
        return;
    }
    
    // キャンセルが洗濯された時
    int cancel_id = this->isEquip ? 2 : 1;
    if (idx == cancel_id)
    {
        this->onMiniSelectorCanceled();
        return;
    }
    
    // 装備処理
    if (this->isEquip)
    {
        Direction dir = idx == 0 ? Direction::RIGHT : Direction::LEFT;
        PlayerDataManager::getInstance()->setItemEquipment(dir, this->selected_item);
    }
    else
    {
        // 装備をはずす
        Direction dir;
        if (this->selected_item == PlayerDataManager::getInstance()->getItemEquipment(Direction::RIGHT))
        {
            dir = Direction::RIGHT;
        }
        if (this->selected_item == PlayerDataManager::getInstance()->getItemEquipment(Direction::LEFT))
        {
            dir = Direction::LEFT;
        }
        PlayerDataManager::getInstance()->setItemEquipment(dir, 0);
        
    }
    
    // 完了メッセージ表示帯
    Sprite* back = Sprite::create();
    back->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT/4));
    back->setColor(Color3B::GRAY);
    back->setPosition(WINDOW_CENTER);
    this->addChild(back);
    
    // 完了メッセージラベル
    string equipMsg = this->isEquip ? "装備しました" : "外しました";
    Label* message = Label::createWithTTF(CsvDataManager::getInstance()->getItemName(this->selected_item) + "を\n" + equipMsg, "fonts/cinecaption2.28.ttf", back->getContentSize().height / 5);
    message->setPosition(Point(message->getContentSize().width / 2 + (WINDOW_WIDTH - message->getContentSize().width)/2, back->getContentSize().height / 2));
    back->addChild(message);
    this->miniSelector->confirm_flag = true;
}

// ミニセレクターを抜け出した時
void ItemMenuLayer::onMiniSelectorCanceled()
{
    SoundManager::getInstance()->playSound("se/back.mp3");
    this->runAction(Sequence::createWithTwoActions(
        CallFunc::create([this](){this->miniSelector->hide();}),
        CallFunc::create([this](){this->listenerKeyboard->setEnabled(true);})
    ));
    if (this->miniSelector->confirm_flag)
    {
        this->onItemMenuCanceled();
        return;
    }
}

// 表示
void ItemMenuLayer::show()
{
    this->listenerKeyboard->setEnabled(true);
    this->setVisible(true);
}

// 非表示
void ItemMenuLayer::hide()
{
    this->listenerKeyboard->setEnabled(false);
    this->setVisible(false);
}

// 戻る
void ItemMenuLayer::onMenuKeyPressed()
{
    FUNCLOG
    if(this->onItemMenuCanceled)
    {
        this->onItemMenuCanceled();
    }
}

// スペースキーを押した時
void ItemMenuLayer::onSpacePressed(int idx)
{
    this->selected_item = this->items[idx];
    this->createMiniSelector();
}

// 選択対象が変わった時
void ItemMenuLayer::onIndexChanged(int newIdx, bool sound)
{
    if (sound)
    {
        SoundManager::getInstance()->playSound("se/cursorMove.mp3");
    }
    for(Node* obj : this->menuObjects)
    {
        if(obj->getTag() == newIdx)
        {
            obj->runAction(FadeTo::create(0.2f, 255));
        }
        else
        {
            obj->runAction(FadeTo::create(0.2f, 100));
        }
    }
    // アイテム詳細を更新
    this->changeItemDiscription(newIdx);
}
