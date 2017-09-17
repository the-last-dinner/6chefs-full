//
//  ResoucesManager.cpp
//  6chefs
//
//  Created by Ryoya Ino on 2017/09/17.
//
//

#include "Managers/ResoucesManager.h"

// 唯一のインスタンスを初期化
static ResoucesManager* _instance = nullptr;

// インスタンスの生成&取得
ResoucesManager* ResoucesManager::getInstance()
{
    if(!_instance) _instance = new ResoucesManager();
    return _instance;
}

// インスタンスの消去
void ResoucesManager::destroy()
{
    delete _instance;
}

// デストラクタ
ResoucesManager::~ResoucesManager()
{
    FUNCLOG
}

// コンストラクタ
ResoucesManager::ResoucesManager()
{
    FUNCLOG
    this->currentPath = "common";
}

// currentパスの切り替え
void ResoucesManager::setCurrentPath(const string &currentPath)
{
    FUNCLOG
    this->currentPath = currentPath;
}

// currentパスからファイルの絶対パスを取得
string ResoucesManager::getCurrentFilePath(const string &fileName)
{
    string currentFilePath = this->currentPath + "/" + fileName;
    return FileUtils::getInstance()->fullPathForFilename(currentFilePath);
}

// commonファイル絶対パスの取得
string ResoucesManager::getCommonFilePath(const string &fileName)
{
    string commonFilePath = "common/" + fileName;
    return FileUtils::getInstance()->fullPathForFilename(commonFilePath);
}
