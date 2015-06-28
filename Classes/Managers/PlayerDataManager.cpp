//
//  PlayerDataManager.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/06/28.
//
//

#include "PlayerDataManager.h"

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

//コンストラクタ
PlayerDataManager::PlayerDataManager()
{FUNCLOG}

//デストラクタ
PlayerDataManager::~PlayerDataManager()
{FUNCLOG}

