//
//  DungeonSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#include "DungeonSceneData.h"

// コンストラクタ
DungeonSceneData::DungeonSceneData()
{
	FUNCLOG
	if(!this->init()) log("初期化に失敗しました。");
}

// デストラクタ
DungeonSceneData::~DungeonSceneData()
{FUNCLOG}

// 初期化
bool DungeonSceneData::init()
{
	FUNCLOG
	
	return true;
}