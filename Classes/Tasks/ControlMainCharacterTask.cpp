//
//  ControlMainCharacterTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#include "Tasks/ControlMainCharacterTask.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "MapObjects/Character.h"

#include "MapObjects/MapObjectList.h"

#include "Tasks/TaskMediator.h"

// コンストラクタ
ControlMainCharacterTask::ControlMainCharacterTask(){FUNCLOG}

// デストラクタ
ControlMainCharacterTask::~ControlMainCharacterTask(){FUNCLOG}

// 初期化
bool ControlMainCharacterTask::init(TaskMediator* mediator)
{
    if(!GameTask::init(mediator)) return false;
    
    return true;
}

// 向きを変える
void ControlMainCharacterTask::turn(const Direction& direction)
{
    Character* mainCharacter {this->mediator->getMapObjectList()->getMainCharacter()};
    if(!mainCharacter->isMoving()) mainCharacter->setDirection(direction);
}

// 目の前を調べる
void ControlMainCharacterTask::search()
{
    MapObjectList* objectList {this->mediator->getMapObjectList()};
    Character* mainCharacter {objectList->getMainCharacter()};
    
    Vector<MapObject*> objs { objectList->getMapObjects(mainCharacter->getCollisionRect(mainCharacter->getDirection()))};
    
    // 現状イベントスクリプトに実行待ちを実装していないため現状はこんな感じで
    for(MapObject* obj : objs)
    {
        if(obj && obj->getTrigger() == Trigger::SEARCH)
        {
            this->mediator->runEventScript(obj->getEventId());
            return;
        }
    }
}

// 歩行中、あたり判定を行い次に向かう位置を決定する
void ControlMainCharacterTask::walking(vector<Direction> directions)
{
    Character* mainCharacter {this->mediator->getMapObjectList()->getMainCharacter()};
    
    // 一番最近押したキーの方向に主人公を向ける
    mainCharacter->setDirection(directions.back());
    
    // ダッシュキーが押されていたら、速度の倍率をあげる
    float ratio {this->mediator->getEventListener()->isPressed(Key::DASH)? 2.f : 1.f};
    
    // 入力確認の頻度を変更
    this->mediator->getEventListener()->setInputCheckInterval(Character::DURATION_FOR_ONE_STEP / ratio);
    
    // 入力から、使う方向の個数を決める
    int directionCount {(directions.size() == 2 && directions.back() != directions.at(directions.size() - 2) && static_cast<int>(directions.back()) + static_cast<int>(directions.at(directions.size() - 2)) != 3)?static_cast<int>(directions.size()):1};
    
    // 入力が２以上の時、斜め方向に当たり判定があるか確認
    bool isHit {(directionCount > 1)?mainCharacter->isHit({directions.back(), directions.at(directionCount - 2)}):false};
    
    // 方向から当たり判定を一方向づつ確認し、移動ベクトルを生成する
    Point movement {Point::ZERO};
    for(int i {static_cast<int>(directions.size()) - 1}; i >= static_cast<int>(directions.size()) - directionCount; i--)
    {
        if((!isHit && !mainCharacter->isHit(directions.at(i))) || (isHit && !mainCharacter->isHit(directions.at(i)) && movement == Point::ZERO))
        {
            movement += MapUtils::getGridVector(directions.at(i));
        }
    }
    // 移動ベクトルがゼロの時リターン
    if(movement == Point::ZERO) return;
    
    this->mediator->runOnScene(Sequence::createWithTwoActions(mainCharacter->createWalkByAction(movement, ratio), CallFunc::create([this](){this->onCharacterWalkedOneGrid();})));
}

// 一マス分移動し終えた時
void ControlMainCharacterTask::onCharacterWalkedOneGrid()
{
    MapObjectList* objectList {this->mediator->getMapObjectList()};
    
    // 衝突判定用Rectの中心座標にあるイベントを呼ぶ
    Rect collisionRect {objectList->getMainCharacter()->getCollisionRect()};
    Point checkPosition {Point(collisionRect.getMidX(), collisionRect.getMidY())};
    MapObject* obj { objectList->getMapObject(checkPosition)};
    
    if(!obj)
    {
        this->riddenEventID = static_cast<int>(EventID::UNDIFINED);
        return;
    }
    
    // 現在乗っているマスのイベントを発動しないようにして、イベントを呼ぶ
    if(obj && obj->getTrigger() == Trigger::RIDE && obj->getEventId() != this->riddenEventID)
    {
        this->riddenEventID = obj->getEventId();
        this->mediator->runEventScript(obj->getEventId());
    }
}