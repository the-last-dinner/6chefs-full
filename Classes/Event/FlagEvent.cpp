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
    this->itemId = stoi(json[member::ITEM_ID].GetString());
    
    return true;
}

void GetItemEvent::run()
{
    PlayerDataManager::getInstance()->setItem(this->itemId);
    
    DungeonSceneManager::getInstance()->getScene()->addChild(SystemMessageLayer::create(SystemMessageData::create(CsvDataManager::getInstance()->getItemName(this->itemId) + "　を手に入れた"), [this]{this->setDone();}), Priority::SYSTEM_MESSAGE);
}

#pragma mark -
#pragma mark RemoveItemEvent

bool RemoveItemEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // アイテムIDを取得
    if(!this->validator->hasMember(json, member::ITEM_ID)) return false;
    this->itemId = stoi(json[member::ITEM_ID].GetString());
    
    return true;
}

void RemoveItemEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->removeItem(this->itemId);
}

#pragma mark -
#pragma mark AddProfileEvent

bool AddProfileEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // キャラクタIDを取得
    if(!this->validator->hasMember(json, member::CHARA_ID)) return false;
    this->charaId = stoi(json[member::CHARA_ID].GetString());
    
    // 情報レベル
    if(!this->validator->hasMember(json, member::INFO_ID)) return false;
    this->infoLevel = stoi(json[member::INFO_ID].GetString());
    
    return true;
}

void AddProfileEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->setCharacterProfile(this->charaId, this->infoLevel);
}

#pragma mark -
#pragma mark ChangeChapterEvent

bool ChangeChapterEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // チャプターID
    if(!this->validator->hasMember(json, member::CHAPTER_ID)) return false;
    this->chapterId = stoi(json[member::CHAPTER_ID].GetString());
    
    return true;
}

void ChangeChapterEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->setChapterId(this->chapterId);
}

#pragma mark -
#pragma mark ChangeLikabilityRatingEvent

bool ChangeLikabilityRatingEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // キャラクタID
    if(!this->validator->hasMember(json, member::CHARA_ID)) return false;
    this->charaId = stoi(json[member::CHARA_ID].GetString());
    
    // 好感度
    if(!this->validator->hasMember(json, member::FAVORITE)) return false;
    this->rating = stoi(json[member::FAVORITE].GetString());
    
    return true;
}

void ChangeLikabilityRatingEvent::run()
{
    this->setDone();
    PlayerDataManager::getInstance()->setFriendship(this->charaId, this->rating);
}
