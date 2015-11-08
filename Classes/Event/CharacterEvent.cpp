//
//  CharacterEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#include "Event/CharacterEvent.h"

#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "MapObjects/Character.h"

#pragma mark CharacterEvent

bool CharacterEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    Character* target {this->validator->getMapObjectById<Character*>(json)};
    
    // nullptrならイベントを生成させない
    if(!target) return false;
    
    this->target = target;
    
    return true;
}

#pragma mark -
#pragma mark ChangeDirectionEvent

bool ChangeDirectionEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    this->direction = this->validator->getDirection(json);
    
    if(this->direction == Direction::SIZE) return false;
    
    return true;
}

void ChangeDirectionEvent::run()
{
    this->target->setDirection(this->direction);
    this->setDone();
}

#pragma mark -
#pragma mark WalkByEvent

bool WalkByEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    this->direction = this->validator->getDirection(json);
    
    this->gridNum = static_cast<int>(json[member::STEPS].GetDouble() * 2);
    
    if(this->direction == Direction::SIZE || this->gridNum == 0) return false;
    
    if(this->validator->hasMember(json, member::SPEED))
    {
       this->speedRatio = json[member::SPEED].GetDouble();
    }
    
    return true;
}

void WalkByEvent::run()
{
    Vector<FiniteTimeAction*> actions {};
    
    for(int i { 0 }; i < this->gridNum; i++)
    {
        actions.pushBack(this->target->createWalkByAction(this->direction, this->speedRatio));
    }
    
    this->target->runAction(Sequence::createWithTwoActions(Sequence::create(actions), CallFunc::create([this]{this->setDone();})));
}

#pragma mark -
#pragma mark WalkToEvent

bool WalkToEvent::init(rapidjson::Value& json)
{
    if(!CharacterEvent::init(json)) return false;
    
    // キャラクタの現在座標と移動先座標の差を取る
    Point diffVector {this->validator->getPoint(json) - this->target->getGridPosition(this->validator->getMapSize())};
    
    int diffX {abs(static_cast<int>(diffVector.x))};
    int diffY {abs(static_cast<int>(diffVector.y))};
    
    // 差の絶対値が大きい方向から処理
    if(diffX >= diffY)
    {
        for(int x { 0 }; x < diffX; x++)
        {
            Direction direction {(diffVector.x < 0)?Direction::LEFT : Direction::RIGHT };
            this->walkActions.pushBack(this->target->createWalkByAction(direction));
        }
        
        for(int y { 0 }; y < diffY; y++)
        {
            Direction direction {(diffVector.y < 0)?Direction::FRONT : Direction::BACK };
            this->walkActions.pushBack(this->target->createWalkByAction(direction));
        }
    }
    else
    {
        for(int y { 0 }; y < diffY; y++)
        {
            Direction direction {(diffVector.y < 0)?Direction::FRONT : Direction::BACK };
            this->walkActions.pushBack(this->target->createWalkByAction(direction));
        }
        
        for(int x { 0 }; x < diffX; x++)
        {
            Direction direction {(diffVector.x < 0)?Direction::LEFT : Direction::RIGHT };
            this->walkActions.pushBack(this->target->createWalkByAction(direction));
        }
    }
    
    return true;
}

void WalkToEvent::run()
{
    if(this->walkActions.empty())
    {
        this->setDone();
        return;
    }
    
    this->target->runAction(Sequence::createWithTwoActions(Sequence::create(this->walkActions), CallFunc::create([this]{this->setDone();})));
}