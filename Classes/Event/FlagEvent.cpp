//
//  FlagEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#include "Event/FlagEvent.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark NeverAgainEvent

bool NeverAgainEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    return true;
}

void NeverAgainEvent::run()
{
    PlayerDataManager::getInstance()->setEventFlag(PlayerDataManager::getInstance()->getLocation().map_id, DungeonSceneManager::getInstance()->getRunningEventId(), true);
    this->setDone();
}

#pragma mark -