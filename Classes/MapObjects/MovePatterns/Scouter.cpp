//
//  Scouter.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#include "MapObjects/MovePatterns/Scouter.h"

#include "Algorithm/PathFinder.h"

#include "MapObjects/MovePatterns/Chaser.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/PathObject.h"

#include "Managers/DungeonSceneManager.h"

#include "Models/Sight.h"

// 定数
const float Scouter::SEARCHING_SPEED_RATIO {0.5f};

// コンストラクタ
Scouter::Scouter() {FUNCLOG};

// デストラクタ
Scouter::~Scouter()
{
    FUNCLOG
    
    CC_SAFE_RELEASE_NULL(this->finder);
    CC_SAFE_RELEASE_NULL(this->sight);
    CC_SAFE_RELEASE_NULL(this->subPattern);
};

// 初期化
bool Scouter::init(Character* character)
{
    if(!MovePattern::init(character)) return false;
    
    PathFinder* finder { PathFinder::create(DungeonSceneManager::getInstance()->getMapSize()) };
    CC_SAFE_RETAIN(finder);
    this->finder = finder;
    
    Sight* sight {Sight::create(character)};
    CC_SAFE_RETAIN(sight);
    this->sight = sight;
    
    return true;
}

// 移動開始
void Scouter::start()
{
    this->move(this->startPathId);
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

// 停止
void Scouter::setPaused(bool paused)
{
    MovePattern::setPaused(paused);
    
    // サブアルゴリズムに対しても適用
    this->subPattern->setPaused(paused);
}

// 主人公一行が移動した時
void Scouter::onPartyMoved() {}

// 次のマップへ移動するか
bool Scouter::canGoToNextMap() const { return false; };

// 次のマップへ出現するまでの時間を取得
float Scouter::calcSummonDelay() const { return 0.f; };

// 動かす
void Scouter::move(const int pathObjId)
{
    if(this->paused) return;
    
    // サブパターンが生成されていればそちらに移動を任せる
    if(this->subPattern)
    {
        this->shiftToSubPattern();
        
        return;
    }
    
    this->chara->lookAround([this, pathObjId]
    {
        // 目的地までの経路を取得
        PathObject* destObj { this->getMapObjectList()->getPathObjectById(pathObjId) };
        this->chara->walkByQueue(this->getPath(destObj), [this, destObj](bool _)
        {
            this->move(this->getMapObjectList()->getPathObjectById(destObj->getNextId())->getPathId());
        }, SEARCHING_SPEED_RATIO);
    });
}

// 指定経路オブジェクトまでの経路を取得
deque<Direction> Scouter::getPath(PathObject* pathObject)
{
    Vector<MapObject*> exclusion {};
    exclusion.pushBack(this->getMainCharacter());
    exclusion.pushBack(this->chara);
    
    deque<Direction> path {this->finder->getPath(this->chara->getGridRect(), this->getMapObjectList()->getGridCollisionRects(exclusion), pathObject->getGridPosition())};
    
    exclusion.clear();
    
    return path;
}

// 毎フレーム呼ばれる視界チェックメソッド
void Scouter::update(float _)
{
    if(!this->sight->isIn(this->getMainCharacter(), this->getMapObjectList())) return;
    
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    
    this->onTargetCameIntoSight();
}

// サブパターンに切り替える
void Scouter::shiftToSubPattern()
{
    MovePattern::setPaused(true);
    
    this->subPattern->start();
    
    this->chara->reaction();
    SoundManager::getInstance()->playSE("agaa.mp3");
}

// 主人公が視界に入った時
void Scouter::onTargetCameIntoSight()
{
    this->chara->clearDirectionsQueue();
    
    // サブパターン生成
    Chaser* sub { Chaser::create(this->chara) };
    sub->setSpeedRatio(this->speedRatio);
    CC_SAFE_RETAIN(sub);
    this->subPattern = sub;
    
    // 移動中じゃなけられば、サブパターンでの移動開始
    if(this->chara->isMoving()) return;
    this->shiftToSubPattern();
}
