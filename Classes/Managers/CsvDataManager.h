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
    // map
    string getMapName(const int map_id);
    string getMapFileName(const int map_id);
    // item
    string getItemName(const int item_id);
    string getItemDiscription(const int item_id);
    // chapter
    string getChapterName(const int chapter_id);
    string getChapterTitle(const int chapter_id);
    // character
    string getCharaName(const int chara_id);
    string getCharaFileName(const int chara_id);
    int getCharaFaceDiff(const int chara_id);
    string getCharaDiscription(const int chara_id, const int level);
    bool isDisplayChara(const int chara_id);
    vector<int> getDisplayCharacters();
};
#endif