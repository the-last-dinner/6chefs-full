//
//  ResouceManager.hpp
//  6chefs
//
//  Created by Ryoya Ino on 2017/09/17.
//
//

#ifndef ResoucesManager_h
#define ResoucesManager_h

#include "define.h"

class ResoucesManager {
    // singleton用関数
public:
    static ResoucesManager* getInstance();
    static void destroy();
private:
    ResoucesManager(); // コンストラクタ
    ~ResoucesManager(); // デストラクタ
    ResoucesManager(const ResoucesManager& other){}; // コピーコンストラクタ
    ResoucesManager& operator = (const ResoucesManager& other); // 代入演算子
    
private:
    string currentPath {};
public:
    void setCurrentPath(const string& currentPath);
    string getCurrentFilePath(const string& fileName);
    string getCommonFilePath(const string& fileName);
};

#endif /* ResoucesManager_h */
