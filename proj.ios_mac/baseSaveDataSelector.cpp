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

// コンストラクタ
baseSaveDataSelector::baseSaveDataSelector()
{FUNCLOG}

// デストラクタ
baseSaveDataSelector::~baseSaveDataSelector()
{FUNCLOG}

// 初期化
bool baseSaveDataSelector::init(const vector<string> datas)
{
	FUNCLOG
	if(!Layer::init()) return false;
	if(!baseMenuLayer::init(1, 5)) return false;
	
	// ベクタから選択肢を生成
	Point center = WINDOW_CENTER;
	Rect panelRect = Rect(0, 0, WINDOW_WIDTH - H_MARGIN * 2, (WINDOW_HEIGHT - V_MARGIN * 2 - EACH_V_MARGIN) / MAX_V_CNT);
	for(int i = 0; i < datas.size();i++)
	{
		Sprite* panel = Sprite::create();
		panel->setTextureRect(panelRect);
		panel->setColor(Color3B::GRAY);
		panel->setPositionX(center.x);
		panel->setPositionY(WINDOW_HEIGHT - (V_MARGIN + i * (EACH_V_MARGIN + panelRect.size.width)));
		this->addChild(panel);
		baseMenuLayer::menuObjects.push_back(panel);
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