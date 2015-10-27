//
//  SoundEvent.cpp
//  LastSupper
//
//  Created by Kohei on 2015/10/25.
//
//

#include "SoundEvent.h"

#include "Event/EventScriptMember.h"

#include "Event/EventScriptValidator.h"

#pragma mark PlayBGM

bool PlayBGM::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(!this->validator->hasMember(json, member::FILE)) return false;
    
    this->fileName = json[member::FILE].GetString();
    
    return true;
}

void PlayBGM::run()
{
    SoundManager::getInstance()->playSound(SoundManager::bgmPath + this->fileName);
    this->setDone();
}

#pragma mark -
#pragma mark PlaySE

bool PlaySE::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(!this->validator->hasMember(json, member::FILE)) return false;
    
    this->fileName = json[member::FILE].GetString();
    
    return true;
}

void PlaySE::run()
{
    SoundManager::getInstance()->playSound(SoundManager::sePath + this->fileName);
    this->setDone();
}