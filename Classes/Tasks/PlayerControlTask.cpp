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
    
    return true;
}

// 向きを変える
void PlayerControlTask::turn(const Key& key, Party* party)
{
    if(!this->enableControl) return;
    
    this->party = party;
    
    Direction direction { MapUtils::keyToDirection(key) };
    Character* mainCharacter {party->getMainCharacter()};
    
    // 主人公が移動中でなければ
    if(!mainCharacter->isMoving())
    {
        // 主人公の向きを変更
        mainCharacter->setDirection(direction);
        
        // 一定時間後に歩行開始
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(PlayerControlTask::startWalking), MapObject::DURATION_MOVE_ONE_GRID);
    }
}

// 歩行開始
void PlayerControlTask::startWalking(float _)
{
    this->walking(DungeonSceneManager::getInstance()->getPressedCursorKeys(), this->party);
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
    
    party->move(moveDirections, ratio, [this, party]{this->onPartyMovedOneGrid(party);});
    
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
void PlayerControlTask::setControlEnable(bool enable)
{
    this->enableControl = enable;
}