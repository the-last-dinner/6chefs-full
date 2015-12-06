//
//  LightEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/02.
//
//

#include "Event/LightEvent.h"

#include "Event/EventScriptMember.h"
#include "Event/EventScriptValidator.h"

#include "Effects/AmbientLightLayer.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark SetAmbientLightEvent

bool SetAmbientLightEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    if(!this->validator->hasMember(json, member::AMBIENT)) return false;
    
    // 環境光の色
    map<string, Color3B> strToColor
    {
        {"basement", AmbientLightLayer::BASEMENT},
        {"day", AmbientLightLayer::DAY},
        {"evening", AmbientLightLayer::EVENING},
        {"night", AmbientLightLayer::NIGHT},
        {"room", AmbientLightLayer::ROOM},
    };
    
    string str {json[member::AMBIENT].GetString()};
    
    if(strToColor.count(str) == 0) return false;
    
    this->color = strToColor[str];
    
    return true;
}

void SetAmbientLightEvent::run()
{
    this->setDone();
    DungeonSceneManager::getInstance()->getAmbientLayer()->setAmbient(this->color);
}
