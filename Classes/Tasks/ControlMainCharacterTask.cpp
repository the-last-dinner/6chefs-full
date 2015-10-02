//
//  ControlMainCharacterTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#include "Tasks/ControlMainCharacterTask.h"

#include "Scenes/DungeonScene.h"

#include "Layers/Dungeon/TiledMapLayer.h"

#include "MapObjects/Character.h"

#include "MapObjects/MapObjectList.h"

// コンストラクタ
ControlMainCharacterTask::ControlMainCharacterTask(){FUNCLOG}

// デストラクタ
ControlMainCharacterTask::~ControlMainCharacterTask(){FUNCLOG}

// 初期化
bool ControlMainCharacterTask::init(DungeonScene* dungeonScene)
{
    this->scene = dungeonScene;
    return true;
}

// 向きを変える
void ControlMainCharacterTask::turn(const Direction& direction)
{
    this->scene->mapLayer->getMainCharacter()->setDirection(direction);
}

// 目の前を調べる
void ControlMainCharacterTask::search()
{
    MapObjectList* objectList {this->scene->mapLayer->getMapObjectList()};
    Character* mainCharacter {objectList->getMainCharacter()};
    
    MapObject* obj { objectList->getMapObject(mainCharacter->getAdjacentPosition({mainCharacter->getDirection(), Direction::SIZE}))};
    if(obj && obj->getTrigger() == Trigger::SEARCH) this->scene->runEvent(obj->getEventId());
}

// 歩行中、あたり判定を行い次に向かう位置を決定する
void ControlMainCharacterTask::walking(stack<Direction> directions)
{
    TiledMapLayer* mapLayer {this->scene->mapLayer};
    Character* mainCharacter {mapLayer->getMainCharacter()};
    
    mainCharacter->setDirection(directions.top());
    
    Direction dirs[2] {};
    
    Point movement {Point::ZERO};
    
    for(int i {0}; i < 2; i++)
    {
        if(directions.size() < 1) break;
        if (!mainCharacter->isHit(directions.top())) movement += MapUtils::getGridVector(directions.top());
        dirs[i] = directions.top();
        directions.pop();
    }
    
    if(mainCharacter->isHit(dirs)) return;
    
    this->scene->runAction(Sequence::create(Spawn::create(CallFunc::create([this, mapLayer, mainCharacter, movement](){mainCharacter->stamp();}),
                                                    TargetedAction::create(mapLayer->getTiledMap(), MoveBy::create(Character::DURATION_FOR_ONE_STEP, - movement)),
                                                    TargetedAction::create(mainCharacter, MoveBy::create(Character::DURATION_FOR_ONE_STEP, movement)),
                                                    nullptr),
                                      CallFunc::create([=]()
                                                       {
                                                           MapObject* obj { mapLayer->getMapObjectList()->getMapObject(mainCharacter->getPosition())};
                                                           if(obj && obj->getTrigger() == Trigger::RIDE) this->scene->runEvent(obj->getEventId());
                                                       }),
                                      nullptr));
}

