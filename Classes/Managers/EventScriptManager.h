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
    vector<string> getPreLoadList(string kind);
private:
    //関数ポインタ型を宣言
    typedef bool (EventScriptManager::*FunctionPointer)(rapidjson::Value& event);
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
    //イベント関数を宣言
    bool changeMap(rapidjson::Value& event);
    bool move(rapidjson::Value& event);
    bool message(rapidjson::Value& event);
};
#endif /* defined(__LastSupper__EventScript__) */
