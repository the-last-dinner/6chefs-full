//
//  SceneEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#include "Event/SceneEvent.h"

#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "Scenes/DungeonScene.h"
#include "Datas/Scene/DungeonSceneData.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"

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
    
    return true;
}

void ChangeMapEvent::run()
{
    this->setDone();
    DungeonSceneManager::getInstance()->changeMap(this->location);
}

#pragma mark -
#pragma mark CameraEvent

bool CameraEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    return true;
}

void CameraEvent::run()
{
    
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