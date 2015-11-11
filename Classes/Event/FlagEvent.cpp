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

#include "Scenes/DungeonScene.h"

#include "Layers/Message/SystemMessageLayer.h"
#include "Datas/Message/SystemMessageData.h"

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
    PlayerDataManager::getInstance()->setItem(this->itemId);
    
    DungeonSceneManager::getInstance()->getScene()->addChild(SystemMessageLayer::create(SystemMessageData::create(CsvDataManager::getInstance()->getItemName(this->itemId) + "　を手に入れた"), [this]{this->setDone();}), Priority::SYSTEM_MESSAGE);
}