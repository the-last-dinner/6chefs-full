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

#pragma mark PlayBGMEvent

bool PlayBGMEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // ファイル名。なければ生成しない
    if(!this->validator->hasMember(json, member::FILE)) return false;
    
    this->fileName = json[member::FILE].GetString();
    
    // 音量
    if(this->validator->hasMember(json, member::VOLUME)) this->volume = json[member::VOLUME].GetDouble();
    
    return true;
}

void PlayBGMEvent::run()
{
    SoundManager::getInstance()->playBGM(this->fileName, true, this->volume);
    this->setDone();
}

#pragma mark -
#pragma mark StopBGMEvent

bool StopBGMEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    return true;
}

void StopBGMEvent::run()
{
    SoundManager::getInstance()->stopBGM();
    this->setDone();
}

#pragma mark -
#pragma mark PlaySEEvent

bool PlaySEEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // ファイル名。なければ生成しない
    if(!this->validator->hasMember(json, member::FILE)) return false;
    
    this->fileName = json[member::FILE].GetString();
    
    // 音量
    if(this->validator->hasMember(json, member::VOLUME)) this->volume = json[member::VOLUME].GetDouble();
    
    return true;
}

void PlaySEEvent::run()
{
    SoundManager::getInstance()->playSE(this->fileName, this->volume);
    this->setDone();
}