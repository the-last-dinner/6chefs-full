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
    bool runEvent(int id, vector<int> spid, vector<Sprite*> sprite);
    std::string trim(const std::string& string, const char* trimCharacterList);
private:
    //クラス変数
    static const map<string, int> EventType;
    //インスタンス変数
    rapidjson::Document json;
    cocos2d::FileUtils* fu;
    //インスタンス用関数(singleton仕様)
    EventScriptManager();                                               // コンストラクタ
    EventScriptManager(const EventScriptManager& other);                // コピーコンストラクタ
    EventScriptManager& operator = (const EventScriptManager& other);   // 代入演算子
    //EventScriptManager関数
    bool dealScript(rapidjson::Value* event, vector<int> spid, vector<Sprite*> sprite);
};
#endif /* defined(__LastSupper__EventScript__) */
