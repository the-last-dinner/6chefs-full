
//
//  PlayerDataManager.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/06/28.

#include "Managers/PlayerDataManager.h"

#include "Models/GlobalPlayerData.h"
#include "Models/LocalPlayerData.h"
#include "Models/StopWatch.h"

#include "Utils/StringUtils.h"
#include "Utils/JsonUtils.h"

#pragma mark Initialize

// 唯一のインスタンスを初期化
static PlayerDataManager* _instance = nullptr;

// インスタンスを生成&取得
PlayerDataManager* PlayerDataManager::getInstance()
{
    if(!_instance) _instance = new PlayerDataManager();
    return _instance;
}

// インスタンスの消去
void PlayerDataManager::destroy()
{
    delete _instance;
    return;
}

//デストラクタ
PlayerDataManager::~PlayerDataManager()
{
    FUNCLOG
    CC_SAFE_RELEASE_NULL(this->timer);
    CC_SAFE_RELEASE_NULL(this->globalData);
    CC_SAFE_RELEASE_NULL(this->localData);
}

// コンストラクタ
PlayerDataManager::PlayerDataManager()
{
    FUNCLOG
    //グローバルセーブデータの読み込み
    this->globalData = GlobalPlayerData::create();
    CC_SAFE_RETAIN(this->globalData);
}

#pragma mark -
#pragma mark

// クリア時の処理
void PlayerDataManager::setGameClear(const int end_id)
{
    // エンディングチェック
    int trophy_id;
    switch (end_id)
    {
        case 0:
            trophy_id = 6;
            break;
        case 1:
            trophy_id = 7;
            break;
        case 2:
            trophy_id = 8;
            break;
    }
    this->globalData->setTrophy(trophy_id);

    // クリアデータの更新
    this->globalData->setBestSaveCount(this->localData->getSaveCount());
    this->globalData->setBestClearTime(this->timer->getTimeInt());
    this->globalData->setTrophyComplete();
    this->globalData->setClearCount(this->localData->getToken());
    
    // グローバルデータをセーブ
    this->globalData->saveGlobalData();
}

//メインとなるローカルデータのidのセット
void PlayerDataManager::setGameStart(const int local_id)
{
    // ローカルデータを取得
    if (!this->localData) CC_SAFE_RELEASE_NULL(this->localData);
    this->localData = LocalPlayerData::create(local_id);
    this->localData->setTrophy = CC_CALLBACK_1(GlobalPlayerData::setTrophy, this->globalData);
    CC_SAFE_RETAIN(this->localData);
    
    // はじめからならトークン生成
    if (local_id == 0) this->localData->setToken();
    
    // プレイ時間計測スタート
    if (!this->timer) CC_SAFE_RELEASE_NULL(this->timer);
    this->timer = StopWatch::create(this->localData->getPlayTime());
    CC_SAFE_RETAIN(this->timer);
    this->timer->tic();
    return;
}

// セーブ
void PlayerDataManager::save(const int local_id)
{
    // ローカルデータのセーブ
    this->localData->setPlayTime(this->timer->getTimeInt());
    this->localData->saveLocalData(local_id);
    
    // グローバルデータのセーブ
    this->globalData->saveGlobalData();
    
    return;
}

#pragma mark -
#pragma mark Getter

// グローバルセーブデータの取得
GlobalPlayerData* PlayerDataManager::getGlobalData() const
{
    return this->globalData;
}

// メインローカルセーブデータの取得
LocalPlayerData* PlayerDataManager::getLocalData() const
{
    return this->localData;
}

// 時間を
string PlayerDataManager::getCurrentTimeForDisplay()
{
    return LastSupper::StringUtils::getTimeForDisplay(this->timer->getTimeInt());
}