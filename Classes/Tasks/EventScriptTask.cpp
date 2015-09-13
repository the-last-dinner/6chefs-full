//
//  EventScriptTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#include "EventScriptTask.h"

#include "Scenes/DungeonScene.h"

// コンストラクタ
EventScriptTask::EventScriptTask(){FUNCLOG}

// デストラクタ
EventScriptTask::~EventScriptTask(){FUNCLOG}

// 初期化
bool EventScriptTask::init(DungeonScene* dungeonScene)
{
	FUNCLOG
	if(!dungeonScene) return false;
	
	this->dungeonScene = dungeonScene;
	
	return true;
}

// イベントスクリプトを実行
void EventScriptTask::runEventScript(int eventId)
{
	CCLOG("EVENT ID >> %d", eventId);
	const rapidjson::Value& action { EventScriptManager::getInstance()->getScript(eventId) };
	//各命令の処理
	if(!action.IsNull()) this->createAction(action);
}

// スクリプトからActionを生成
FiniteTimeAction* EventScriptTask::createAction(const rapidjson::Value& json)
{
	return nullptr;
}