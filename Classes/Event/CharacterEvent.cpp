//
//  CharacterEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#include "Event/CharacterEvent.h"

#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "Layers/Dungeon/TiledMapLayer.h"

#include "MapObjects/Character.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark CharacterEvent

bool CharacterEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(!this->validator->hasMember(json, member::OBJECT_ID)) return false;
    
    this->objectId = json[member::OBJECT_ID].GetString();
    
    return true;
}

bool CharacterEvent::onRun()
{
    Character* target { this->validator->getMapObjectById<Character*>(this->objectId) };
    if(!target)
    {
        this->setDone();
        
        return false;
    }
    
    this->target = target;
    
    return true;
}

#pragma mark -
#pragma mark ChangeDirectionEvent

bool ChangeDirectionEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    this->direction = this->validator->getDirection(json);
    
    if(this->direction == Direction::SIZE) return false;
    
    return true;
}

void ChangeDirectionEvent::run()
{
    if(!CharacterEvent::onRun()) return;
    
    this->target->setDirection(this->direction);
    this->setDone();
}

#pragma mark -
#pragma mark WalkByEvent

bool WalkByEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    this->direction = this->validator->getDirection(json);
    
    this->gridNum = static_cast<int>(json[member::STEPS].GetDouble() * 2);
    
    if(this->direction == Direction::SIZE || this->gridNum == 0) return false;
    
    if(this->validator->hasMember(json, member::SPEED)) this->speedRatio = json[member::SPEED].GetDouble();
    
    return true;
}

void WalkByEvent::run()
{
    if(!CharacterEvent::onRun()) return;
    
    vector<Direction> dirs { this->direction };
    this->target->walkBy(dirs, this->gridNum, [this]{this->setDone();}, this->speedRatio);
}

#pragma mark -
#pragma mark WalkToEvent

bool WalkToEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    // 目的地座標をcocos座標系で保持
    this->destPosition = this->validator->getPoint(json);
    
    return true;
}

void WalkToEvent::run()
{
    if(!CharacterEvent::onRun()) return;
    
    Vec2 movement {this->destPosition - this->target->getGridPosition()};

    this->target->walkBy(MapUtils::vecToDirection(movement), static_cast<int>(movement.getLength()), [this]{this->setDone();});
}