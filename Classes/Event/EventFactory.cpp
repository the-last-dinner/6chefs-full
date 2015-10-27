//
//  EventFactory.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/24.
//
//

#include "Event/EventFactory.h"

#include "Event/GameEvent.h"
#include "Event/MapObjectEvent.h"
#include "Event/ModalLayerEvent.h"
#include "Event/SoundEvent.h"
#include "Event/SceneEvent.h"

#include "Event/EventScriptMember.h"

// コンストラクタ
EventFactory::EventFactory() {FUNCLOG};

// デストラクタ
EventFactory::~EventFactory() {FUNCLOG};

// 初期化
bool EventFactory::init()
{
    return true;
}

// ゲームイベントを生成して返す
GameEvent* EventFactory::createGameEvent(rapidjson::Value& json)
{
    map<string, function<GameEvent*(rapidjson::Value&)>> pCreateFuncs
    {
        // 制御系
        {"sequence", EventSequence::create},    //順番に処理を実行
        {"spawn", EventSpawn::create},          //同時に処理を実行
        {"if", EventIf::create},                     // 場合分け処理
        
        // 音系
        {"playSE", PlaySE::create},             //効果音再生
        {"playBGM", PlayBGM::create},           //BGM再生
        
        // メッセージ系
        {"charaMsg", CharacterMessage::create},         //キャラメッセージ
        {"storyMsg", StoryMessage::create},             //ストーリーメッセージ
        {"systemMsg", SystemMessage::create},           //システムのメッセージ
        
        // 画面遷移系
        {"changeMap", ChangeMap::create},               //マップ移動
        {"camera", CameraEvent::create},                // カメラ
        
        // マップオブジェクト系
        {"reaction", Reaction::create},                 // リアクション
    };
    
    // イベントタイプがなければ同時実行を生成して返す
    if(!json.IsObject() || !json.HasMember(member::TYPE)) return EventSpawn::create(json);
    
    // イベントタイプ名取得
    string typeName {json[member::TYPE].GetString()};
    
    if(pCreateFuncs.count(typeName) == 0)
    {
        CCLOG("Undifined EventScript Type : %s", typeName.c_str());
        return nullptr;
    }
    
    return pCreateFuncs.at(typeName)(json);
}

// イベントベクタを生成
Vector<GameEvent*> EventFactory::createEventVector(rapidjson::Value& json)
{
    Vector<GameEvent*> events {};
    
    rapidjson::Value& eventJson {(json.IsObject() && json.HasMember(member::ACTION))?json[member::ACTION]:json};
    
    for(int i { 0 }; i < eventJson.Size(); i++)
    {
        if(GameEvent* event { this->createGameEvent(eventJson[i]) })
        {
            events.pushBack(event);
        }
    }
    
    return events;
}

// イベントキューを生成
queue<GameEvent*> EventFactory::createEventQueue(rapidjson::Value& json)
{
    queue<GameEvent*> events {};
    \
    rapidjson::Value& eventJson {(json.IsObject() && json.HasMember(member::ACTION))?json[member::ACTION]:json};
    
    for (int i { 0 }; i < eventJson.Size(); i++)
    {
        if(GameEvent* event { this->createGameEvent(eventJson[i]) })
        {
            CC_SAFE_RETAIN(event);
            events.push(event);
        }
    }
    
    return events;
}