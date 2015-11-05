//
//  EventScriptValidator.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/24.
//
//

#include "Event/EventScriptValidator.h"

#include "Event/EventScriptMember.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"

// コンストラクタ
EventScriptValidator::EventScriptValidator() {FUNCLOG};

// デストラクタ
EventScriptValidator::~EventScriptValidator() {FUNCLOG};

// 初期化
bool EventScriptValidator::init() {return true;}

// メンバーが存在するかどうか
bool EventScriptValidator::hasMember(rapidjson::Value& json, const char* member)
{
    return json.HasMember(member);
}

// condition情報からboolを算出
bool EventScriptValidator::detectCondition(rapidjson::Value& json)
{
    if(!this->hasMember(json, member::CONDITION)) return false;
    
    map<string, bool(EventScriptValidator::*)(rapidjson::Value&, bool)> pConditionFuncs
    {
        {"equip", &EventScriptValidator::detectEquipFlg},
        {"event", &EventScriptValidator::detectEventFlg},
        {"flg", &EventScriptValidator::detectFlg},
        {"item", &EventScriptValidator::detectItemFlg},
        {"status", &EventScriptValidator::detectStatusFlg},
    };
    
    rapidjson::Value& conditions {json[member::CONDITION]};
    
    bool detection { false };

    for(int i { 0 }; i < conditions.Size(); i++)
    {
        for(rapidjson::Value::MemberIterator itr = conditions[i].MemberBegin(); itr != conditions[i].MemberEnd(); itr++)
        {
            string key {itr->name.GetString()};
            bool negative {false};
            
            if(key.find("N") == 0)
            {
                key = LastSupper::StringUtils::strReplace("N", "", key);
                negative = true;
            }
            
            // N判定
            detection = (this->*pConditionFuncs[key])(itr->value, negative);
            
            //ANDなのでfalseがあったらbreak;
            if(!detection) break;
        }
        //ORなのでtrueがあったらbreak;してreturn;
        if(detection) break;
    }
    return detection;
}

// 装備状態の確認
bool EventScriptValidator::detectEquipFlg(rapidjson::Value& json, bool negative)
{
    bool detection { false };

    for(int i { 0 }; i < json.Size(); i++)
    {
        detection = PlayerDataManager::getInstance()->checkItemEquipment(stoi(json[i].GetString()));
        if(negative) detection = !detection;
        if(!detection) break;
    }
    
    return detection;
}

// イベントを見たか確認
bool EventScriptValidator::detectEventFlg(rapidjson::Value& json, bool negative)
{
    bool detection { false };
    
    //複数のイベントの場合
    if(json[0].IsArray())
    {
        for(int i { 0 }; i < json.Size(); i++)
        {
            detection = PlayerDataManager::getInstance()->getEventFlag(stoi(json[i][0].GetString()), stoi(json[i][1].GetString()));
            if(negative) detection = !detection;
            if(!detection) return false;
        }
        
    }
    //一つのイベントの場合
    else
    {
        detection = PlayerDataManager::getInstance()->getEventFlag(stoi(json[0].GetString()), stoi(json[1].GetString()));
        if(negative) detection = !detection;
    }
    
    return detection;
}

// フラグの確認
bool EventScriptValidator::detectFlg(rapidjson::Value& json, bool negative)
{
    return false;
}

// アイテム所持の確認
bool EventScriptValidator::detectItemFlg(rapidjson::Value& json, bool negative)
{
    bool detection { false };
    
    // 複数の場合
    if(json.IsArray())
    {
        for(int i { 0 }; i < json.Size(); i++)
        {
            detection = PlayerDataManager::getInstance()->checkItem(stoi(json[i].GetString()));
            if(negative) detection = !detection;
            if(!detection) break;
        }
    }
    // 一つの場合
    else
    {
        detection = PlayerDataManager::getInstance()->checkItem(stoi(json.GetString()));
        if(negative) detection = !detection;
    }
    
    return detection;
}

// 好感度の確認
bool EventScriptValidator::detectStatusFlg(rapidjson::Value& json, bool negative)
{
    bool detection { false };
    
    //複数の好感度
    if(json[0].IsArray())
    {
        for(int i { 0 }; i < json.Size(); i++)
        {
            detection = PlayerDataManager::getInstance()->checkFriendship(json[i][0].GetString(), stoi(json[i][1].GetString()));
            if(negative) detection = !detection;
            if(!detection) break;
        }
    }
    // 一つの時
    else
    {
        detection = PlayerDataManager::getInstance()->checkFriendship(json[0].GetString(), stoi(json[1].GetString()));
        if(negative) detection = !detection;
    }
    
    return detection;
}

// マップオブジェクトを取得
MapObject* EventScriptValidator::getMapObjectById(rapidjson::Value& json)
{
    if(!this->hasMember(json, member::OBJECT_ID)) return nullptr;
    
    string sObjid = json[member::OBJECT_ID].GetString();
    
    // heroであったら主人公を返す
    if (sObjid == "hero")
    {
        return DungeonSceneManager::getInstance()->getParty()->getMainCharacter();
    }
    // heroでなければIDから検索して返す
    else
    {
        MapObject* obj { DungeonSceneManager::getInstance()->getMapObjectList()->getMapObject(stoi(sObjid)) };
        
        return obj;
    }
}

// x,yの組を取得
Point EventScriptValidator::getPoint(rapidjson::Value& json)
{
    if(!this->hasMember(json, member::X) || !this->hasMember(json, member::Y)) return Point::ZERO;
    
    return Point(json[member::X].GetInt(), json[member::Y].GetInt());
}

// 方向を取得
Direction EventScriptValidator::getDirection(rapidjson::Value& json)
{
    if(!this->hasMember(json, member::DIRECTION)) return Direction::SIZE;
    
    return MapUtils::toEnumDirection(json[member::DIRECTION].GetString());
}