//
//  PlayerControlTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#include "Tasks/PlayerControlTask.h"

#include "MapObjects/Character.h"
#include "MapObjects/MapObject.h"
#include "MapObjects/MapObjectList.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"

// コンストラクタ
PlayerControlTask::PlayerControlTask(){FUNCLOG}

// デストラクタ
PlayerControlTask::~PlayerControlTask(){FUNCLOG}

// 初期化
bool PlayerControlTask::init()
{
    if(!GameTask::init()) return false;
    
    EventListenerKeyboardLayer* listener {DungeonSceneManager::getInstance()->getSceneEventListener()};
    if(!listener) return false;
    this->listener = listener;
    
    Party* party { DungeonSceneManager::getInstance()->getParty() };
    if(!party) return false;
    this->party = party;
    
    return true;
}

// 向きを変える
void PlayerControlTask::turn(const Key& key)
{
    Direction direction { MapUtils::keyToDirection(key) };
    Character* mainCharacter {this->party->getMainCharacter()};
    if(!mainCharacter->isMoving()) mainCharacter->setDirection(direction);
}

// 目の前を調べる
void PlayerControlTask::search()
{
    MapObjectList* objectList {DungeonSceneManager::getInstance()->getMapObjectList()};
    Character* mainCharacter {this->party->getMainCharacter()};
    
    Vector<MapObject*> objs { objectList->getMapObjects(mainCharacter->getCollisionRect(mainCharacter->getDirection()))};
    
    // 同座標にあるイベントを全て発動
    Point objPosition {Point::ZERO};
    for(MapObject* obj : objs)
    {
        if(obj && obj->getTrigger() == Trigger::SEARCH && (objPosition == Point::ZERO || obj->getPosition() == objPosition))
        {
            objPosition = obj->getPosition();
            DungeonSceneManager::getInstance()->runEvent(obj->getEventId());
        }
    }
}

// 歩行中、あたり判定を行い次に向かう位置を決定する
void PlayerControlTask::walking(const vector<Key>& keys)
{
    vector<Direction> directions { MapUtils::keyToDirection(keys) };
    
    Character* mainCharacter {this->party->getMainCharacter()};
    
    // 一番最近押したキーの方向に主人公を向ける
    mainCharacter->setDirection(directions.back());
    
    // ダッシュキーが押されていたら、速度の倍率をあげる
    float ratio {DungeonSceneManager::getInstance()->isPressed(Key::DASH)? 2.f : 1.f};
    
    // 入力確認の頻度を変更
    DungeonSceneManager::getInstance()->setInputCheckInterval(MapObject::DURATION_MOVE_ONE_GRID / ratio);
    
    // 入力から、使う方向の個数を決める
    int directionCount {(directions.size() == 2 && directions.back() != directions.at(directions.size() - 2) && static_cast<int>(directions.back()) + static_cast<int>(directions.at(directions.size() - 2)) != 3)?static_cast<int>(directions.size()):1};
    
    // 入力が２以上の時、斜め方向に当たり判定があるか確認
    bool isHit {(directionCount > 1)?mainCharacter->isHit({directions.back(), directions.at(directionCount - 2)}):false};
    
    // 方向から当たり判定を一方向づつ確認し、移動方向に詰める
    vector<Direction> moveDirections {};
    for(int i {static_cast<int>(directions.size()) - 1}; i >= static_cast<int>(directions.size()) - directionCount; i--)
    {
        if((!isHit && !mainCharacter->isHit(directions.at(i))) || (isHit && !mainCharacter->isHit(directions.at(i)) && moveDirections.empty()))
        {
            moveDirections.push_back(directions.at(i));
        }
    }
    
    if(moveDirections.empty()) return;
    
    // 衝突判定用Rectの中心点を含むイベントをキューにつめる
    Rect collisionRect {};
    if(moveDirections.size() == 1)
    {
        collisionRect = mainCharacter->getCollisionRect(moveDirections[0]);
    }
    else
    {
        collisionRect = mainCharacter->getCollisionRect({moveDirections[0], moveDirections[1]});
    }
    
    Vector<MapObject*> objs { DungeonSceneManager::getInstance()->getMapObjectList()->getMapObjects(collisionRect) };
    
    // 主人公を無視
    if(objs.size() == 1 && objs.at(0) == this->party->getMainCharacter())
    {
        this->riddenEventID = static_cast<int>(EventID::UNDIFINED);
    }
    
    for(MapObject* obj : objs)
    {
        if(obj && obj->getTrigger() == Trigger::RIDE && obj->getEventId() != this->riddenEventID)
        {
            if(this->riddenEventID == static_cast<int>(EventID::UNDIFINED)) this->riddenEventID = obj->getEventId();
            DungeonSceneManager::getInstance()->pushEventBack(obj->getEventId());
        }
    }
    
    this->party->move(moveDirections, ratio, CC_CALLBACK_0(PlayerControlTask::onPartyMovedOneGrid, this));
}

// 一マス分移動し終えた時
void PlayerControlTask::onPartyMovedOneGrid()
{
    // キューにあるイベントを実行
    DungeonSceneManager::getInstance()->runEventQueue();
}