//
//  DebugManager.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/06.
//
//

#include "Managers/DebugManager.h"
#include "Utils/JsonUtils.h"

// 定数
const char* DebugManager::STATS {"stats"};
const char* DebugManager::DEBUG_MASK {"debug_mask"};
const char* DebugManager::INVINCIBLE_MODE {"invincible_mode"};


// 唯一のインスタンスを初期化
static DebugManager* _instance = nullptr;

#pragma mark Core

// インスタンスの生成&取得
DebugManager* DebugManager::getInstance()
{
    if(!_instance) _instance = new DebugManager();
    return _instance;
}

// インスタンスの消去
void DebugManager::destroy()
{
    delete _instance;
}

// デストラクタ
DebugManager::~DebugManager(){FUNCLOG}

// コンストラクタ
DebugManager::DebugManager()
{
    FUNCLOG
    string path = FileUtils::getInstance()->fullPathForFilename("debug_config.json");
    if (path == "") return;
    this->debugConfig = LastSupper::JsonUtils::readJsonFile(path);
    this->hasDebugConfig = true;
}

// スタッツを表示するかどうか
bool DebugManager::displayStats()
{
    if (!this->hasDebugConfig) return false;
    return this->debugConfig[STATS].GetBool();
}

// MapのDebugMaskを表示するかどうか
bool DebugManager::displayDebugMask()
{
    if (!this->hasDebugConfig) return false;
    return this->debugConfig[DEBUG_MASK].GetBool();
}

// 無敵モードかどうか
bool DebugManager::isInvincibleMode()
{
    if (!this->hasDebugConfig) return false;
    return this->debugConfig[INVINCIBLE_MODE].GetBool();
}
