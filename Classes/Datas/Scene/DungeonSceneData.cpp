//
//  DungeonSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#include "Datas/Scene/DungeonSceneData.h"

#include "Event/EventScript.h"

// コンストラクタ
DungeonSceneData::DungeonSceneData(){FUNCLOG}

// デストラクタ
DungeonSceneData::~DungeonSceneData()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->eventScript);
}

// 初期化
bool DungeonSceneData::init(const PlayerDataManager::Location& location)
{
	FUNCLOG
    
    // イベントスクリプト生成
    EventScript* eventScript {EventScript::create(CsvDataManager::getInstance()->getMapFileName(location.map_id))};
    CC_SAFE_RETAIN(eventScript);
    this->eventScript = eventScript;

	// プリロード用リストを取得
    this->soundFilePaths = eventScript->getPreLoadList("sound");
    this->textureFilePaths = eventScript->getPreLoadList("texture");
	
	this->textureFilePaths.push_back("frame");
	this->textureFilePaths.push_back("ui");
    this->textureFilePaths.push_back("obj");
	
	return true;
}

// イベントスクリプトを取得
EventScript* DungeonSceneData::getEventScript() const
{
    return this->eventScript;
}