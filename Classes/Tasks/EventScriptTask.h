//
//  EventScriptTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#ifndef __LastSupper__EventScriptTask__
#define __LastSupper__EventScriptTask__

#include "Common.h"

class DungeonScene;

class EventScriptTask : public Ref
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(EventScriptTask, DungeonScene*)
	
	// インスタンスメソッド
private:
	EventScriptTask();
	~EventScriptTask();
	virtual bool init(DungeonScene* dungeonScene);
	FiniteTimeAction* createAction(const rapidjson::Value& json);
public:
	void runEventScript(int eventId);
	
	// インスタンス変数
private:
	DungeonScene* dungeonScene {nullptr};
	
	
	//イベント関数
private:
	Ref* sequence(const rapidjson::Value& event);
	Ref* spawn(const rapidjson::Value& event);
	Ref* repeat(const rapidjson::Value& event);
	Ref* flagif(const rapidjson::Value& event);
	Ref* changeMap(const rapidjson::Value& event);
	Ref* move(const rapidjson::Value& event);
	Ref* message(const rapidjson::Value& event);
	Ref* talk(const rapidjson::Value& event);
	Ref* fade(const rapidjson::Value& event);
	Ref* playSE(const rapidjson::Value& event);
	Ref* playBGM(const rapidjson::Value& event);
	Ref* control(const rapidjson::Value& event);
	Ref* read(const rapidjson::Value& event);
};

#endif /* defined(__LastSupper__EventScriptTask__) */
