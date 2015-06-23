//
//  EventScript.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#ifndef __LastSupper__EventScriptManager__
#define __LastSupper__EventScriptManager__

#include "define.h"

class EventScriptManager
{
public:
    //インスタンス用関数(singleton仕様)
    static EventScriptManager* getInstance();
    static void destroy();
    ~EventScriptManager();
    //EventScriptManager関数
    bool setEventScript(string script);
    bool setDungeonScene(Layer* mainLayer);
    bool runEvent(int id);
    vector<string> getPreLoadList(string type);
private:
    //関数ポインタ型を宣言
    typedef Ref*(EventScriptManager::*FunctionPointer)(rapidjson::Value& event);
    //クラス変数
    map<string, FunctionPointer> event_map;
    //インスタンス変数
    rapidjson::Document json;
    cocos2d::FileUtils* fu;
    cocos2d::Layer* layer;
    //インスタンス用関数(singleton仕様)
    EventScriptManager();                                               // コンストラクタ
    EventScriptManager(const EventScriptManager& other);                // コピーコンストラクタ
    EventScriptManager& operator = (const EventScriptManager& other);   // 代入演算子
    //EventScriptManager関数
    bool dealScript(rapidjson::Value& event);
    cocos2d::Vector<FiniteTimeAction*> createActionVec(rapidjson::Value& subAction);
    //イベント関数を宣言
    Ref* sequence(rapidjson::Value& event);
    Ref* spawn(rapidjson::Value& event);
    Ref* repeat(rapidjson::Value& event);
    Ref* flagif(rapidjson::Value& event);
    Ref* changeMap(rapidjson::Value& event);
    Ref* move(rapidjson::Value& event);
    Ref* message(rapidjson::Value& event);
    Ref* talk(rapidjson::Value& event);
    Ref* fade(rapidjson::Value& event);
    Ref* playSE(rapidjson::Value& event);
    Ref* playBGM(rapidjson::Value& event);
    Ref* control(rapidjson::Value& event);
    Ref* read(rapidjson::Value& event);
};
#endif /* defined(__LastSupper__EventScript__) */
