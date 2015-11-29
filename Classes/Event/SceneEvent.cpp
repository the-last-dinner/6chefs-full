//
//  SceneEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#include "Event/EventFactory.h"
#include "Event/SceneEvent.h"

#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "Datas/Scene/DungeonCameraSceneData.h"
#include "Datas/Scene/DungeonSceneData.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"
#include "Models/StopWatch.h"

#include "Scenes/DungeonCameraScene.h"
#include "Scenes/DungeonScene.h"

#pragma mark ChangeMapEvent

bool ChangeMapEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    Direction direction {Direction::SIZE};

    // directionの指定がされている時
    if(this->validator->hasMember(json, member::DIRECTION))
    {
        direction = MapUtils::toEnumDirection(json[member::DIRECTION].GetString());
    }
    // directionが指定されていない時
    else
    {
        direction = DungeonSceneManager::getInstance()->getParty()->getMainCharacter()->getDirection();
    }
    
    this->location = Location(stoi(json[member::MAP_ID].GetString()), json[member::X].GetInt(), json[member::Y].GetInt(), direction);
    
    // 移動後に実行するイベントID
    if(this->validator->hasMember(json, member::EVENT_ID)) this->initEventId = stoi(json[member::EVENT_ID].GetString());
    
    return true;
}

void ChangeMapEvent::run()
{
    this->setDone();
    DungeonSceneManager::getInstance()->changeMap(this->location, this->initEventId);
}

#pragma mark -
#pragma mark CreateCameraEvent

bool CreateCameraEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // 映したい場所
    this->location.map_id = (this->validator->hasMember(json, member::MAP_ID)) ? stoi(json[member::MAP_ID].GetString()) : PlayerDataManager::getInstance()->getLocation().map_id;
 
    Point position { this->validator->getPoint(json) };
    this->location.x = position.x;
    this->location.y = position.y;
    
    // ターゲット
    if(this->validator->hasMember(json, member::OBJECT_ID)) this->objId = stoi(json[member::OBJECT_ID].GetString());
    
    // イベント
    if(!this->validator->hasMember(json, member::ACTION)) return false;
    this->event = this->factory->createGameEvent(json[member::ACTION]);
    
    return true;
}

void CreateCameraEvent::run()
{
    DungeonCameraSceneData* data { DungeonCameraSceneData::create(this->location) };
    data->setTargetId(this->objId);
    
    DungeonCameraScene* scene { DungeonCameraScene::create(data, this->event, [this]{DungeonSceneManager::getInstance()->popCameraScene(); this->setDone();}) };
    DungeonSceneManager::getInstance()->pushCameraScene(scene);
}

#pragma mark -
#pragma mark MoveCameraEvent

bool MoveCameraEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // 目的地
    this->toPosition = this->validator->getToPoint(json);
    
    // 移動時間
    if(this->validator->hasMember(json, member::TIME)) this->duration = json[member::TIME].GetDouble();
    
    return true;
}

void MoveCameraEvent::run()
{
    DungeonSceneManager::getInstance()->moveCamera(this->toPosition, this->duration, [this]{this->setDone();});
}

#pragma mark -
#pragma mark WaitEvent

bool WaitEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    float duration {static_cast<float>(json[member::TIME].GetDouble())};
    
    // 0秒指定だったらfalseを返す（falseを返すと生成されない）
    if(duration == 0.f) return false;
    
    this->duration = duration;
    
    return true;
}

void WaitEvent::run()
{
    DungeonSceneManager::getInstance()->getScene()->runAction(Sequence::createWithTwoActions(DelayTime::create(this->duration), CallFunc::create([this](){this->setDone();})));
}

#pragma mark -
#pragma mark FadeOutEvent

bool FadeOutEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(this->validator->hasMember(json, member::TIME)) this->duration = json[member::TIME].GetDouble();
    
    if(this->validator->hasMember(json, member::COLOR))
    {
        rapidjson::Value& colorJson { json[member::COLOR] };
        this->color = Color3B(colorJson[0].GetInt(), colorJson[1].GetInt(), colorJson[2].GetInt());
    }
    
    return true;
}

void FadeOutEvent::run()
{
    DungeonSceneManager::getInstance()->fadeOut(this->color, this->duration, [this]{this->setDone();});
}

#pragma mark -
#pragma mark FadeInEvent

bool FadeInEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(this->validator->hasMember(json, member::TIME)) this->duration = json[member::TIME].GetDouble();
    
    return true;
}

void FadeInEvent::run()
{
    DungeonSceneManager::getInstance()->fadeIn(this->duration, [this]{this->setDone();});
}

#pragma mark -
#pragma mark CountDown

bool CountDownEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // 制限時間
    if(!this->validator->hasMember(json, member::SECOND)) return false;
    this->second = json[member::SECOND].GetDouble();
    
    // conditionを保存
    if (this->validator->hasMember(json, member::CONDITION))
    {
        this->equip = stoi(json[member::CONDITION][0][member::EQUIP][0].GetString());
        this->checkEquip = true;
    }
    
    // 成功時イベント
    if(this->validator->hasMember(json, member::TRUE_))
    {
        if(json[member::TRUE_].IsString()) this->sEventId = stoi(json[member::TRUE_].GetString());
        if(json[member::TRUE_].IsArray()) this->sEvent = this->factory->createGameEvent(json[member::TRUE_]);
        CC_SAFE_RETAIN(this->sEvent);
    }
    
    // 失敗時イベント
    if (this->validator->hasMember(json, member::FALSE_))
    {
        if(json[member::FALSE_].IsString()) this->fEventId = stoi(json[member::FALSE_].GetString());
        if(json[member::FALSE_].IsArray()) this->fEvent = this->factory->createGameEvent(json[member::FALSE_]);
        CC_SAFE_RETAIN(this->fEvent);
    }
    if (this->validator->hasMember(json, member::ACTION))
    {
        if(json[member::ACTION].IsString()) this->fEventId = stoi(json[member::ACTION].GetString());
        if(json[member::ACTION].IsArray()) this->fEvent = this->factory->createGameEvent(json[member::ACTION]);
        CC_SAFE_RETAIN(this->fEvent);
    }
    
    return true;
}

void CountDownEvent::run()
{
    StopWatch* stopWatch = DungeonSceneManager::getInstance()->getStopWatch();
    
    stopWatch->setCountDown(this);
    
    stopWatch->scheduleCallback = [this](double time)
    {
        // 条件チェック
        bool condition = false;
        if(this->checkEquip)
        {
            condition = PlayerDataManager::getInstance()->checkItemEquipment(this->equip);
        }
        
        // 条件を満たしていた場合
        if (condition)
        {
            CC_SAFE_RELEASE_NULL(this->fEvent);
            if(this->sEvent)
            {
                DungeonSceneManager::getInstance()->pushEventFront(this->sEvent);
            }
            else
            {
                // ID指定の場合
                DungeonSceneManager::getInstance()->pushEventFront(this->sEventId);
            }
            DungeonSceneManager::getInstance()->runEventQueue();
            return false;
        }
        CCLOG("COUNT DOWN >> %f", this->second - time);
        // 時間切れチェック
        if (static_cast<float>(time) >= this->second)
        {
            CC_SAFE_RELEASE_NULL(this->sEvent);
            if(this->fEvent)
            {
                DungeonSceneManager::getInstance()->pushEventFront(this->fEvent);
            }
            else
            {
                // ID指定の場合
                DungeonSceneManager::getInstance()->pushEventFront(this->fEventId);
            }
            DungeonSceneManager::getInstance()->runEventQueue();
            return false;
        }
        return true;
    };
    
    // カウントダウンスタート
    stopWatch->startCountDown(0.5f);
    
    this->setDone();
}

#pragma mark -
#pragma mark StopCount

bool StopCountEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    return true;
}

void StopCountEvent::run()
{
    DungeonSceneManager::getInstance()->pauseStopWatch();
    DungeonSceneManager::getInstance()->releaseStopWatch();
    this->setDone();
}