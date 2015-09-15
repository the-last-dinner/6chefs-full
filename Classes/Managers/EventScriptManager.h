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
#include "Managers/PlayerDataManager.h"

class EventScriptManager
{
//singleton用関数
public:
    static EventScriptManager* getInstance();
    static void destroy();
private:
    EventScriptManager();   // コンストラクタ
    ~EventScriptManager();  // デストラクタ
    EventScriptManager(const EventScriptManager& other){};                // コピーコンストラクタ
    EventScriptManager& operator = (const EventScriptManager& other);   // 代入演算子

//インスタンス変数
private:
    rapidjson::Document json;
    cocos2d::FileUtils* fu;
    string map_id;
//通常関数
public:
    //イベントスクリプトセット
    bool setEventScript(string script);
    //音楽などのリソースのプリロード
    vector<string> getPreLoadList(string type);
    //該当IDスクリプトの取得
	rapidjson::Value& getScript(int eventId);
    //map_idの取得
    string getMapId();
};
#endif /* defined(__LastSupper__EventScript__) */
