//
//  baseSaveDataSelector.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/20.
//
//

#include "baseSaveDataSelector.h"

const int baseSaveDataSelector::EACH_V_MARGIN = WINDOW_HEIGHT * 0.05;
const int baseSaveDataSelector::H_MARGIN = WINDOW_WIDTH * 0.1f;
const int baseSaveDataSelector::V_MARGIN = WINDOW_HEIGHT * 0.1f;
const int baseSaveDataSelector::MAX_V_CNT = 5;
const float baseSaveDataSelector::INNER_H_MARGIN_RATIO = 0.05f;
const float baseSaveDataSelector::INNER_V_MARGIN_RATIO = 0.05f;

// コンストラクタ
baseSaveDataSelector::baseSaveDataSelector()
{FUNCLOG}

// デストラクタ
baseSaveDataSelector::~baseSaveDataSelector()
{FUNCLOG}

// 初期化
bool baseSaveDataSelector::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	if(!baseMenuLayer::init(1, 5)) return false;
	
	// セーブデータリストを取得
	vector<PlayerDataManager::SaveIndex> datas = PlayerDataManager::getInstance()->getSaveList();
	
	Point center = WINDOW_CENTER;
	Rect panelRect = Rect(0, 0, WINDOW_WIDTH - H_MARGIN * 2, (WINDOW_HEIGHT - V_MARGIN * 2 - EACH_V_MARGIN) / MAX_V_CNT);
	for(int i = 0; i < datas.size();i++)
	{
		PlayerDataManager::SaveIndex data = datas.at(i);
		Sprite* panel = Sprite::create();
		panel->setTextureRect(panelRect);
		panel->setColor(Color3B::GRAY);
		panel->setPositionX(center.x);
		panel->setPositionY(WINDOW_HEIGHT - (V_MARGIN + i * (EACH_V_MARGIN + panelRect.size.width)));
		this->addChild(panel);
		baseMenuLayer::menuObjects.push_back(panel);
		
		// 表示ラベルを生成
		// データ名
		Label* name = Label::createWithTTF(data.name, "fonts/cinecaption2.28.ttf", panelRect.size.height * 0.6f);
		name->setPosition(Point(name->getContentSize().width / 2 + panelRect.size.width * INNER_H_MARGIN_RATIO, panelRect.size.height / 2));
		panel->addChild(name);
		
		// マップ名
		Label* mapName = Label::createWithTTF(data.map_name, "fonts/cinecaption2.28.ttf", panelRect.size.height * 0.2f);
		mapName->setPosition(Point(panelRect.size.width - mapName->getContentSize().width / 2 - panelRect.size.width * INNER_H_MARGIN_RATIO, panelRect.size.height * 0.75f));
		panel->addChild(mapName);
		
		// プレイ時間
		Label* time = Label::createWithTTF(data.play_time, "fonts/cinecaption2.28.ttf", panelRect.size.height * 0.2f);
		time->setPosition(Point(panelRect.size.width - time->getContentSize().width / 2 - panelRect.size.width * INNER_V_MARGIN_RATIO, panelRect.size.height * 0.25f));
		panel->addChild(time);
	}
	
	return true;
}

// カーソル移動時
void baseSaveDataSelector::moveCursor(bool sound)
{
	return;
}

// 決定キーを押した時
void baseSaveDataSelector::onSpacePressed()
{
	return;
}