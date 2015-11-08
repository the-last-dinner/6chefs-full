//
//  MapEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#include "Event/MapEvent.h"

#include "Event/EventScriptMember.h"
#include "Event/EventScriptValidator.h"

#include "Layers/Dungeon/TiledMapLayer.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark HideLayerEvent

bool HideLayerEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    this->layerName = json[member::LAYER].GetString();
    
    return true;
}

void HideLayerEvent::run()
{
    DungeonSceneManager::getInstance()->getMapLayer()->hideLayer(this->layerName);
    this->setDone();
}