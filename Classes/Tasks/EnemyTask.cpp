//
//  EnemyTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/21.
//
//

#include "Tasks/EnemyTask.h"

#include "MapObjects/Enemy.h"

#include "Managers/DungeonSceneManager.h"

// コンストラクタ
EnemyTask::EnemyTask() {FUNCLOG};

// デストラクタ
EnemyTask::~EnemyTask() {FUNCLOG};

// 初期化
bool EnemyTask::init()
{
    if(!GameTask::init()) return false;
    
    // 配置すべき敵の情報を格納
    this->datas = DungeonSceneManager::getInstance()->getEnemyDatas();
    
    return true;
}

// 出現を開始
void EnemyTask::start(const int mapId)
{
    if(this->datas.empty()) return;
    
    for(int i { 0 }; i < this->datas.size(); i++)
    {
        EnemyData data { this->datas.at(i) };
        
        if(data.to_map_id != mapId) continue;
        
        this->runAction(Sequence::createWithTwoActions(DelayTime::create(data.summon_delay), CallFunc::create([this, data, i, mapId]
        {
            EnemyData newData { data };
            newData.chara_data.location.map_id = mapId;
            newData.chara_data.location.x = newData.to_x;
            newData.chara_data.location.y = newData.to_y;
            
            DungeonSceneManager::getInstance()->addEnemy(Enemy::create(newData));
            
            mutex mtx;
            
            mtx.lock();
            this->datas.erase(this->datas.begin() + i);
            mtx.unlock();
        })));
    }
}

// 現在配置されている敵と、配置予定の敵から、次マップへの敵情報を生成する
vector<EnemyData> EnemyTask::createDatas(const Vector<Enemy*>& enemies, const Location& destLocation, const Location& currentLocation)
{
    vector<EnemyData> datas {};
    
    // 現在配置されている敵について
    if(!enemies.empty())
    {
        for(Enemy* enemy : enemies)
        {
            EnemyData data {enemy->getEnemyData()};
            
            // マップ間移動不可なら、行き先マップIDに現在のマップIDを格納
            if(!enemy->canGoToNextMap())
            {
                data.to_map_id = data.chara_data.location.map_id;
                data.summon_delay = 0.0f;
                datas.push_back(data);
                
                continue;
            }
            
            // 移動可能なら、行き先マップIDを格納
            data.to_map_id = destLocation.map_id;
            
            // 出現する座標を格納
            data.to_x = destLocation.x;
            data.to_y = destLocation.y;
            
            // 次マップに出現するまでの遅延時間を格納
            data.summon_delay = enemy->calcSummonDelay();
            
            datas.push_back(data);
        }
    }
    
    // まだ配置されていない敵について
    if(!this->datas.empty())
    {
        for(EnemyData data : this->datas)
        {
            // 行き先マップIDが、元々配置されていた場所だった時
            if(data.chara_data.location.map_id == destLocation.map_id)
            {
                // 出現座標を、元いた座標に設定
                data.to_map_id = destLocation.map_id;
                data.to_x = data.chara_data.location.x;
                data.to_y = data.chara_data.location.y;
                
                // 出現までの遅延時間を０に
                data.summon_delay = 0.0f;
                
                datas.push_back(data);
                
                continue;
            }
            
            // 行き先マップIDが、元々配置されていない場所だった時
            // 行き先を格納
            data.to_map_id = destLocation.map_id;
            data.to_x = data.chara_data.location.x;
            data.to_y = data.chara_data.location.y;
            
            // 出現遅延時間+2秒
            data.summon_delay += 2.0f;
            
            datas.push_back(data);
        }
    }
    
    return datas;
}