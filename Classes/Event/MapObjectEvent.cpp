//
//  MapObjectEvent.cpp
//  LastSupper
//
//  Created by Kohei on 2015/10/25.
//
//

#include "MapObjectEvent.h"

#include "Event/EventScriptValidator.h"

#include "MapObjects/MapObject.h"


#pragma mark MapObjectEvent

bool MapObjectEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    MapObject* target {this->validator->getMapObjectById(json)};
    
    // nullptrならイベントを生成させない
    if(!target) return false;
    
    this->target = target;
    
    return true;
}

#pragma mark -
#pragma mark ReactionEvent

bool ReactionEvent::init(rapidjson::Value& json)
{
    if(!MapObjectEvent::init(json)) return false;
    
    return true;
}

void ReactionEvent::run()
{
    Sprite* icon {Sprite::createWithSpriteFrameName("icon_sign.png")};
    icon->setPosition(Point(0, this->target->getContentSize().height));
    icon->setScaleY(0.01f);
    this->target->addChild(icon);
    
    icon->runAction(Sequence::create(EaseElasticOut::create(ScaleTo::create(0.6f, 1.f), 0.5f), DelayTime::create(1.f), RemoveSelf::create(), CallFunc::create([this](){this->setDone();}), nullptr));
}
