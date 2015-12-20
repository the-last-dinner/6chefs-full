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
const char* DebugManager::CRYPT {"crypt"};
const char* DebugManager::SAVE {"save"};
const char* DebugManager::CSV {"csv"};
const char* DebugManager::EVENT_SCRIPT {"event_script"};

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
    this->file_path = FileUtils::getInstance()->fullPathForFilename("debug_config.json");
    if (this->file_path == "") return;
    this->debugConfig = LastSupper::JsonUtils::readJsonFile(this->file_path);
    this->hasDebugConfig = true;
}

// DebugConfigの書き出し
void DebugManager::writeConfig()
{
    LastSupper::JsonUtils::writeJsonFile(this->file_path, this->debugConfig);
}

// スタッツを表示するかどうか
bool DebugManager::displayStats()
{
    if (!this->hasDebugConfig) return false;
    if (!this->debugConfig.HasMember(STATS)) return false;
    return this->debugConfig[STATS].GetBool();
}

// MapのDebugMaskを表示するかどうか
bool DebugManager::displayDebugMask()
{
    if (!this->hasDebugConfig) return false;
    if (!this->debugConfig.HasMember(DEBUG_MASK)) return false;
    return this->debugConfig[DEBUG_MASK].GetBool();
}

// 無敵モードかどうか
bool DebugManager::isInvincibleMode()
{
    if (!this->hasDebugConfig) return false;
    if (!this->debugConfig.HasMember(INVINCIBLE_MODE)) return false;
    return this->debugConfig[INVINCIBLE_MODE].GetBool();
}

// セーブデータの初期暗号化が必要かどうか
bool DebugManager::isCryptedSaveData()
{
    if (!this->hasDebugConfig) return true;
    if (!this->debugConfig.HasMember(CRYPT)) return true;
    if (!this->debugConfig[CRYPT].HasMember(SAVE)) return true;
    return this->debugConfig[CRYPT][SAVE].GetBool();
}

// セーブデータの暗号化をセット
void DebugManager::setCryptedSaveData()
{
    if (!this->hasDebugConfig) return;
    if (!this->debugConfig.HasMember(CRYPT)) return;
    if (!this->debugConfig[CRYPT].HasMember(SAVE)) return;
    this->debugConfig[CRYPT][SAVE].SetBool(true);
    this->writeConfig();
}