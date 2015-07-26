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

//クラス変数
private:
    //関数ポインタ型を宣言
    typedef Ref*(EventScriptManager::*FunctionPointer)(rapidjson::Value& event);
    //関数ポインタリンクマップ
    map<string, FunctionPointer> event_map;

//インスタンス変数
private:
    rapidjson::Document json;
    cocos2d::FileUtils* fu;
    cocos2d::Layer* layer;

//通常関数
public:
    //イベントスクリプトセット
    bool setEventScript(string script);
    //マップ初期化処理
    bool setDungeonScene(Layer* mainLayer);
    //idのイベントを実行
    bool runEvent(int id);
    //音楽などのリソースのプリロード
    vector<string> getPreLoadList(string type);
private:
    //スクリプト処理関数
    bool dealScript(rapidjson::Value& event);
    cocos2d::Vector<FiniteTimeAction*> createActionVec(rapidjson::Value& subAction);
    //イベント関数
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
