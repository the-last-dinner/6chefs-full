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
//クラス変数
private:
    //関数ポインタ型を宣言
    typedef Ref*(EventScriptTask::*FunctionPointer)(rapidjson::Value& event);
    typedef bool(EventScriptTask::*FunctionPointerC)(rapidjson::Value& condition, bool reverse);
    //関数ポインタリンクマップ
    const static map<string, FunctionPointer> EVENT_MAP;
    const static map<string, FunctionPointerC> CONDITION_MAP;
    
    //インスタンス変数
private:
    DungeonScene* scene {nullptr};
    int event_status;
// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(EventScriptTask, DungeonScene*)
	
// インスタンスメソッド
private:
	EventScriptTask();
	~EventScriptTask();
	virtual bool init(DungeonScene* dungeonScene);
    //スクリプト処理関数
    void dealScript(rapidjson::Value& action);
    cocos2d::Vector<FiniteTimeAction*> createActionVec(rapidjson::Value& sub_act);
public:
	void runEventScript(int eventId);
	
//イベント関数
private:
	Ref* sequence(rapidjson::Value& event);
	Ref* spawn(rapidjson::Value& event);
	Ref* repeat(rapidjson::Value& event);
	Ref* ifelse(rapidjson::Value& event);
	Ref* changeMap(rapidjson::Value& event);
	Ref* move(rapidjson::Value& event);
    Ref* storyMsg(rapidjson::Value& event);
    Ref* charaMsg(rapidjson::Value& event);
    Ref* questionMsg(rapidjson::Value& event);
	Ref* systemMsg(rapidjson::Value& event);
	Ref* reaction(rapidjson::Value& event);
	Ref* fade(rapidjson::Value& event);
	Ref* playSE(rapidjson::Value& event);
	Ref* playBGM(rapidjson::Value& event);
	Ref* control(rapidjson::Value& event);
	Ref* read(rapidjson::Value& event);
    Ref* changeFlg(rapidjson::Value& event);
    Ref* fadein(rapidjson::Value& event);
    Ref* fadeout(rapidjson::Value& event);
    Ref* changeDirection(rapidjson::Value& event);
    Ref* charaWalkTo(rapidjson::Value& event);
    Ref* createChara(rapidjson::Value& event);
    //if
    bool judgeCondition(rapidjson::Value& cond);
    bool eventIf(rapidjson::Value& cond, bool reverse);
    bool itemIf(rapidjson::Value& cond, bool reverse);
    bool flagIf(rapidjson::Value& cond, bool reverse);
    bool equipIf(rapidjson::Value& cond, bool reverse);
    bool statusIf(rapidjson::Value& cond, bool reverse);
    //util
    string strReplace(const string& pattern, const string& replacement, string target);
};

#endif /* defined(__LastSupper__EventScriptTask__) */
