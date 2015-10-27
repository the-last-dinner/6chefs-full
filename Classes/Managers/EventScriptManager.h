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

class EventScriptValidator;
class EventFactory;

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
    EventFactory* factory { nullptr };
    EventScriptValidator* validator { nullptr };
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
    
    void setValidator(EventScriptValidator* validator);
    
    EventFactory* getFactory() const;
    EventScriptValidator* getValidator() const;
};
#endif /* defined(__LastSupper__EventScript__) */
