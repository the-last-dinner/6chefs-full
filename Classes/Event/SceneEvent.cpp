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

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"

#pragma mark ChangeMap

bool ChangeMap::init(rapidjson::Value& json)
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
        direction = this->validator->getMapObjectList()->getMainCharacter()->getDirection();
    }
    
    this->location = PlayerDataManager::Location(stoi(json[member::MAP_ID].GetString()), json[member::X].GetInt(), json[member::Y].GetInt(), direction);
    
    return true;
}

void ChangeMap::run()
{
    PlayerDataManager::getInstance()->setLocation(this->location);
    this->setDone();
    Director::getInstance()->replaceScene(DungeonScene::createScene());
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