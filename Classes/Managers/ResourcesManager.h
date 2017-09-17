//
//  ResouceManager.hpp
//  6chefs
//
//  Created by Ryoya Ino on 2017/09/17.
//
//

#ifndef ResourcesManager_h
#define ResourcesManager_h

#include "define.h"

class ResourcesManager {
    // singleton用関数
public:
    static ResourcesManager* getInstance();
    static void destroy();
private:
    ResourcesManager(); // コンストラクタ
    ~ResourcesManager(); // デストラクタ
    ResourcesManager(const ResourcesManager& other){}; // コピーコンストラクタ
    ResourcesManager& operator = (const ResourcesManager& other); // 代入演算子
    
private:
    string currentPath {};
public:
    void setCurrentPath(const string& currentPath);
    string getCurrentPath();
    string getCurrentFilePath(const string& fileName);
    string getCommonFilePath(const string& fileName);
};

#endif /* ResourcesManager_h */
