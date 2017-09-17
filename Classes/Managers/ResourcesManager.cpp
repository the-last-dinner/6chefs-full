//
//  ResourcesManager.cpp
//  6chefs
//
//  Created by Ryoya Ino on 2017/09/17.
//
//

#include "Managers/ResourcesManager.h"

// 唯一のインスタンスを初期化
static ResourcesManager* _instance = nullptr;

// インスタンスの生成&取得
ResourcesManager* ResourcesManager::getInstance()
{
    if(!_instance) _instance = new ResourcesManager();
    return _instance;
}

// インスタンスの消去
void ResourcesManager::destroy()
{
    delete _instance;
}

// デストラクタ
ResourcesManager::~ResourcesManager()
{
    FUNCLOG
}

// コンストラクタ
ResourcesManager::ResourcesManager()
{
    FUNCLOG
    this->currentPath = "common";
}

// currentパスの取得
string ResourcesManager::getCurrentPath()
{
    return this->currentPath;
}

// currentパスの切り替え
void ResourcesManager::setCurrentPath(const string &currentPath)
{
    FUNCLOG
    this->currentPath = currentPath;
}

// currentパスからファイルの絶対パスを取得
string ResourcesManager::getCurrentFilePath(const string &fileName)
{
    string currentFilePath = this->currentPath + "/" + fileName;
    return FileUtils::getInstance()->fullPathForFilename(currentFilePath);
}

// commonファイル絶対パスの取得
string ResourcesManager::getCommonFilePath(const string &fileName)
{
    string commonFilePath = "common/" + fileName;
    return FileUtils::getInstance()->fullPathForFilename(commonFilePath);
}
