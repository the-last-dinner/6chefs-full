//
//  DungeonSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#include "Datas/Scene/DungeonSceneData.h"

// コンストラクタ
DungeonSceneData::DungeonSceneData(){FUNCLOG}

// デストラクタ
DungeonSceneData::~DungeonSceneData(){FUNCLOG}

// 初期化
bool DungeonSceneData::init()
{
	FUNCLOG

	// プリロード用リストを取得
	this->soundFilePaths = EventScriptManager::getInstance()->getPreLoadList("sound");
	this->textureFilePaths = EventScriptManager::getInstance()->getPreLoadList("texture");
	
	this->textureFilePaths.push_back("frame");
	this->textureFilePaths.push_back("ui");
    this->textureFilePaths.push_back("obj");
	
	return true;
}
