//
//  PlayerControlTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#include "Tasks/PlayerControlTask.h"

#include "MapObjects/Character.h"
#include "MapObjects/MapObjectList.h"
#include "MapObjects/Party.h"

#include "Managers/DungeonSceneManager.h"

// 定数
const string PlayerControlTask::START_WALKING_SCHEDULE_KEY { "start_walking" };

// コンストラクタ
PlayerControlTask::PlayerControlTask(){FUNCLOG}

// デストラクタ
PlayerControlTask::~PlayerControlTask(){FUNCLOG}

// 初期化
bool PlayerControlTask::init()
{
    if(!GameTask::init()) return false;
    
    return true;
}

// 向きを変える
void PlayerControlTask::turn(const Key& key, Party* party)
{
    if(!this->enableControl) return;
    
    Direction direction { MapUtils::keyToDirection(key) };
    Character* mainCharacter {party->getMainCharacter()};
    
    // 主人公が移動中でなければ
    if(!mainCharacter->isMoving())
    {
        // 主人公の向きを変更
        mainCharacter->setDirection(direction);
        
        // 一定時間後に歩行開始
        if(!this->isScheduled(START_WALKING_SCHEDULE_KEY)) this->scheduleOnce([this, party](float _)
        {
            this->walking(DungeonSceneManager::getInstance()->getPressedCursorKeys(), party);
        }, MapObject::DURATION_MOVE_ONE_GRID, START_WALKING_SCHEDULE_KEY);
    }
}

// 目の前を調べる
void PlayerControlTask::search(Party* party)
{
    if(!this->enableControl) return;
    
    MapObjectList* objectList {DungeonSceneManager::getInstance()->getMapObjectList()};
    Character* mainCharacter {party->getMainCharacter()};
    
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
void PlayerControlTask::walking(const vector<Key>& keys, Party* party)
{
    if(keys.empty() || !this->enableControl) return;
    
    vector<Direction> directions { MapUtils::keyToDirection(keys) };
    
    Character* mainCharacter {party->getMainCharacter()};
    
    // 一番最近押したキーの方向に主人公を向ける
    mainCharacter->setDirection(directions.back());
    
    // ダッシュキーが押されていたら、速度の倍率をあげる
    float ratio {DungeonSceneManager::getInstance()->isPressed(Key::DASH)? 2.f : 1.f};
    
    // 入力から、使う方向の個数を決める
    int directionCount {(directions.size() == 2 && directions.back() != directions.at(directions.size() - 2) && static_cast<int>(directions.back()) + static_cast<int>(directions.at(directions.size() - 2)) != 3)?static_cast<int>(directions.size()):1};
    
    vector<Direction> moveDirections {};
    for(int i { 0 }; i < directions.size(); i++)
    {
        if(directions.size() - directionCount > i) continue;
        moveDirections.push_back(directions.at(i));
    }
    
    if(!party->move(moveDirections, ratio, [this, party]{this->onPartyMovedOneGrid(party);})) return;
    
    Vector<MapObject*> objs { DungeonSceneManager::getInstance()->getMapObjectList()->getMapObjectsByGridRect(mainCharacter->getGridRect(), Trigger::RIDE) };
    
    // 何も見つからなかった場合は、UNDIFINEDをセットする
    if(objs.empty())
    {
        this->riddenEventID = static_cast<int>(EventID::UNDIFINED);
        
        return;
    }
    
    for(MapObject* obj : objs)
    {
        if(obj->getEventId() != this->riddenEventID)
        {
            if(this->riddenEventID == static_cast<int>(EventID::UNDIFINED)) this->riddenEventID = obj->getEventId();
            DungeonSceneManager::getInstance()->pushEventBack(obj->getEventId());
        }
    }
}

// 一マス分移動し終えた時
void PlayerControlTask::onPartyMovedOneGrid(Party* party)
{
    // キューにあるイベントを実行
    DungeonSceneManager::getInstance()->runEventQueue();
    
    this->walking(DungeonSceneManager::getInstance()->getPressedCursorKeys(), party);
}

// 操作可能状態か設定
void PlayerControlTask::setControlEnable(bool enable, Party* party)
{
    this->enableControl = enable;
    
    // 有効にされた時は、入力しているキーに応じて移動開始
    if(enable)
    {
        this->walking(DungeonSceneManager::getInstance()->getPressedCursorKeys(), party);
    }
}