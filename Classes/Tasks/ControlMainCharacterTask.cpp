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
    this->scene->mapLayer->getMapObjectList()->getMainCharacter()->setDirection(direction);
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
void ControlMainCharacterTask::walking(vector<Direction> directions)
{
    TiledMapLayer* mapLayer {this->scene->mapLayer};
    Character* mainCharacter {mapLayer->getMapObjectList()->getMainCharacter()};
    
    mainCharacter->setDirection(directions.back());
    
    int directionCount {(directions.size() >= 2 && directions.back() != directions.at(directions.size() - 2))?static_cast<int>(directions.size()):1};
    
    bool isHit {(directionCount > 1)?mainCharacter->isHit({directions.back(), directions.at(directionCount - 2)}):false};
    
    Point movement {Point::ZERO};
    
    for(int i {directionCount - 1}; i >= 0; i--)
    {
        if((!isHit && !mainCharacter->isHit(directions.at(i))) || (isHit && !mainCharacter->isHit(directions.at(i)) && movement == Point::ZERO))
        {
            movement += MapUtils::getGridVector(directions.at(i));
        }
    }
    
    this->scene->runAction(Sequence::create(Spawn::create(TargetedAction::create(mainCharacter, MoveBy::create(Character::DURATION_FOR_ONE_STEP, movement)),
                                                          nullptr),
                                      CallFunc::create([mapLayer, mainCharacter, this]()
                                                       {
                                                           MapObject* obj { mapLayer->getMapObjectList()->getMapObject(mainCharacter->getPosition())};
                                                           if(obj && obj->getTrigger() == Trigger::RIDE) this->scene->runEvent(obj->getEventId());
                                                       }),
                                      nullptr));
}

