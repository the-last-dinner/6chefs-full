//
//  SaveDataSelector.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/20.
//
//

#include "Layers/Menu/SaveDataSelector.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "Scenes/DungeonScene.h"
#include "Datas/Scene/DungeonSceneData.h"
#include "UI/NotificationBand.h"

// 定数
const float SaveDataSelector::INNER_H_MARGIN_RATIO = 0.05f;
const float SaveDataSelector::INNER_V_MARGIN_RATIO = 0.05f;

// コンストラクタ
SaveDataSelector::SaveDataSelector(){FUNCLOG}

// デストラクタ
SaveDataSelector::~SaveDataSelector(){FUNCLOG}

// 初期化
bool SaveDataSelector::init(bool write = false)
{
	FUNCLOG
	if(!MenuLayer::init(2, MAX_SAVE_COUNT / 2)) return false;
	
    // フラグをセット
    this->write_flag = write;
    this->comfirm_flag = false;
	// 黒い背景を生成
	Sprite* black = Sprite::create();
	black->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	black->setColor(Color3B::BLACK);
	black->setPosition(WINDOW_CENTER);
	this->addChild(black);
	
	// セーブデータリストを取得
	this->saveDatas = PlayerDataManager::getInstance()->getSaveList();
	
	Point center = WINDOW_CENTER;
	for(int i = 0; i < this->saveDatas.size();i++)
	{
		PlayerDataManager::SaveIndex data {this->saveDatas.at(i)};
		Sprite* panel {Sprite::createWithSpriteFrameName("save_frame.png")};
		Size panelSize {panel->getContentSize()};
		panel->setPosition((panelSize.width / 2) * (2 * (i % 2) + 1), WINDOW_HEIGHT - (panelSize.height / 2) * (2 * (i / 2) + 1));
		panel->setTag(i);
		this->addChild(panel);
		this->menuObjects.push_back(panel);
		
		// 表示ラベルを生成
		// データ名
		Label* name = Label::createWithTTF(data.chapter, "fonts/cinecaption2.28.ttf", panelSize.height / 5);
		name->setPosition(Point(name->getContentSize().width / 2 + panelSize.width * INNER_H_MARGIN_RATIO, panel->getContentSize().height / 2));
		panel->addChild(name);
		
		// マップ名
		Label* mapName = Label::createWithTTF(data.map_name, "fonts/cinecaption2.28.ttf", panelSize.height / 6);
		mapName->setPosition(Point(panelSize.width - mapName->getContentSize().width / 2 - panelSize.width * INNER_H_MARGIN_RATIO, panelSize.height * 0.75f));
		panel->addChild(mapName);
		
		// プレイ時間
		Label* time = Label::createWithTTF(data.play_time, "fonts/cinecaption2.28.ttf", panelSize.height / 6);
		time->setPosition(Point(panelSize.width - time->getContentSize().width / 2 - panelSize.width * INNER_V_MARGIN_RATIO, panelSize.height * 0.25f));
		panel->addChild(time);
		
		// 不透明度を半分にしておく
		panel->setCascadeOpacityEnabled(true);
		panel->setOpacity(100);
	}
    
    // デフォルトセレクト
	this->setCascadeOpacityEnabled(true);
    int id = PlayerDataManager::getInstance()->getSaveDataId();
    int index = (id <= 0) ? 0 : id - 1;
    this->setSelectedIndex(index);
	this->onIndexChanged(index, false);
	
	return true;
}

// 表示
void SaveDataSelector::show()
{
	this->setVisible(true);
	this->listenerKeyboard->setEnabled(true);
}

// 非表示
void SaveDataSelector::hide()
{
	this->listenerKeyboard->setEnabled(false);
	this->setVisible(false);
}

// 選択しているindexが変わった時
void SaveDataSelector::onIndexChanged(int newIdx, bool sound)
{
    // セーブしましたがでてる場合は無視
    if(this->comfirm_flag) return;
    // 移動音
    if (sound)
    {
        SoundManager::getInstance()->playSE("cursorMove.mp3");
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
}

// 決定キーを押した時
void SaveDataSelector::onSpacePressed(int idx)
{
    // インクリメント
    idx++;
    // 確認時
    if (this->comfirm_flag)
    {
        if(this->onSaveDataSelectCancelled)
        {
            this->onSaveDataSelectCancelled();
        }
        this->comfirm_flag = false;
        return;
    }
    // セーブorロード
    if (this->write_flag)
    {
        // セーブ時
        SoundManager::getInstance()->playSE("save.mp3");
        PlayerDataManager::getInstance()->save(idx);
        
        // 完了メッセージ表示
        NotificationBand* notification {NotificationBand::create("セーブが完了しました")};
        notification->setBandColor(Color3B(64,0,0));
        this->addChild(notification);
        this->comfirm_flag = true;
    }
    else
    {
        // ロード時
        if(PlayerDataManager::getInstance()->checkSaveDataExists(idx))
        {
            // ロード
            SoundManager::getInstance()->playSE("load.mp3");
            PlayerDataManager::getInstance()->setMainLocalData(idx);
            Director::getInstance()->replaceScene(DungeonScene::create(DungeonSceneData::create(PlayerDataManager::getInstance()->getLocation())));
        } else
        {
            // セーブデータが存在しない
            SoundManager::getInstance()->playSE("failure.mp3");
        }
    }
    return;
}

// メニューキーを押した時
void SaveDataSelector::onMenuKeyPressed()
{
	if(this->onSaveDataSelectCancelled)
	{
		this->onSaveDataSelectCancelled();
	}
}