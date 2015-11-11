//
//  FlagEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#include "Event/FlagEvent.h"

#include "Event/EventScriptMember.h"
#include "Event/EventScriptValidator.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark NeverAgainEvent

bool NeverAgainEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    return true;
}

void NeverAgainEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->setEventFlag(PlayerDataManager::getInstance()->getLocation().map_id, DungeonSceneManager::getInstance()->getRunningEventId(), true);
}

#pragma mark -
#pragma mark GetItemEvent

bool GetItemEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // アイテムIDを取得
    if(!this->validator->hasMember(json, member::ITEM_ID)) return false;
    this->itemId = json[member::ITEM_ID].GetInt();
    
    return true;
}

void GetItemEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->setItem(this->itemId);
}