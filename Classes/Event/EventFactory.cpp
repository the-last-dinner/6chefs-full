//
//  EventFactory.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/24.
//
//

#include "Event/EventFactory.h"

#include "Event/CharacterEvent.h"
#include "Event/FlagEvent.h"
#include "Event/GameEvent.h"
#include "Event/MapEvent.h"
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
        {"sequence", EventSequence::create},    // 順番に処理を実行
        {"spawn", EventSpawn::create},          // 同時に処理を実行
        {"if", EventIf::create},                // 場合分け処理
        
        // 音系
        {"playBGM", PlayBGMEvent::create},           // BGM再生
        {"stopBGM", StopBGMEvent::create},           // BGM停止
        {"playSE", PlaySEEvent::create},             // 効果音再生
        
        // モーダルレイヤ系
        {"charaMsg", CharacterMessage::create},         // キャラメッセージ
        {"storyMsg", StoryMessage::create},             // ストーリーメッセージ
        {"systemMsg", SystemMessage::create},           // システムのメッセージ
        {"displayImg", DispImageEvent::create},         // 画像表示
        
        // シーン系
        {"changeMap", ChangeMapEvent::create},          // マップ移動
        {"camera", CameraEvent::create},                // カメラ
        {"wait", WaitEvent::create},                    // 時間待機
        {"fadeout", FadeOutEvent::create},               // フェードアウト
        {"fadein", FadeInEvent::create},                // フェードイン
        
        // マップ系
        {"removeLayer", HideLayerEvent::create},        // マップの指定レイヤを非表示
        
        // マップオブジェクト系
        {"createChara", CreateMapObjectEvent::create},      // マップオブジェクトを無効リストから有効リストへ移動、マップ上に表示
        {"reaction", ReactionEvent::create},                // リアクション
        
        // キャラクター系
        {"changeDirection", ChangeDirectionEvent::create},  // 方向転換
        {"charaWalkTo", WalkToEvent::create},               // 指定座標へ歩行
        {"charaWalk", WalkByEvent::create},                 // 方向、歩数をして歩行
        
        // フラグ系
        {"already", NeverAgainEvent::create},               // イベントIDを見たことにし、二度と発動しないようにする
        {"getItem", GetItemEvent::create},                  // アイテムを入手
        {"addProfile", AddProfileEvent::create},            // プロフィールに情報を追加する
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