//
//  CsvDataManager.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/09/13.
//
//

#ifndef LastSupper_CsvDataManager_h
#define LastSupper_CsvDataManager_h

#include "define.h"

class CsvDataManager
{
public:
    enum struct DataType
    {
        MAP,
        ITEM,
        CHARACTER,
        CHAPTER
    };
private:
    static const map<DataType, string> file_type;
    map<DataType, map<int, vector<string>>> csv_data;
//インスタンス変数
private:
    //FileUtils
    cocos2d::FileUtils* fu;
public:
    
//singleton用関数
public:
    static CsvDataManager* getInstance();
    static void destroy();
private:
    CsvDataManager(); // コンストラクタ
    ~CsvDataManager(); // デストラクタ
    CsvDataManager(const CsvDataManager& other){}; // コピーコンストラクタ
    CsvDataManager& operator = (const CsvDataManager& other); // 代入演算子
//関数
private:
    map<int, vector<string>> readCsvFile(string file_name);
public:
    string getDisplayName(const DataType& data_type, int data_id);
    string getFileName(const DataType& data_type, int data_id);
    int existsFaceDiff(const DataType& data_type, int data_id);
};

#endif
