//
//  PlayerDataManager.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/06/28.
//
//

#ifndef __LastSupper__PlayerDataManager__
#define __LastSupper__PlayerDataManager__

#include "define.h"

class PlayerDataManager
{
//構造体
public:
    struct SaveIndex
    {
        int data_id;
        string name;
        string play_time;
        string save_count;
        string map_name;
        SaveIndex(int i, const string& n, const string& pt, const string& sc, const string& mn):data_id(i), name(n), play_time(pt), save_count(sc), map_name(mn){};
        SaveIndex(){};
    };
//クラス変数
private:
    static const int MAX_SAVE_COUNT;

//インスタンス変数
private:
    //グローバルセーブデータ
    rapidjson::Document global;
    //対象ローカルセーブデータ
    int local_id;
    //ローカルセーブデータ達
    vector<rapidjson::Document> local;
    //FileUtils
    cocos2d::FileUtils* fu;

//通常関数
public:
    //全ローカルデータのセット
    void setLocalDataAll();
    //メインとなるローカルデータのセット
    void setMainLocalData(const int& id);
    //ローカルセーブデータリストの取得
    vector<SaveIndex> getSaveList();
    //セーブ
    void save(const int& id);
private:
    //グローバルデータのセット
    bool setGlobalData();
    //セーブデータを全初期化
    void initializeFiles();
    //文字列置換(後でUtilsに行くかも)
    string strReplace(const string& pattern, const string& replacement, string target);
    string getSprintf(const string& format, const string& str);
    //JSONファイル読み込み
    rapidjson::Document readJsonFile(const string& path);
    //JSONファイル書き出し
    void writeJsonFile(const string& path, const rapidjson::Document& doc);

//singleton用関数
public:
    static PlayerDataManager* getInstance();
    static void  destroy();
private:
    PlayerDataManager();    //コンストラクタ
    ~PlayerDataManager();   //デストラクタ
    PlayerDataManager(const PlayerDataManager& other){};              //コピーコンストラクタ
    PlayerDataManager& operator = (const PlayerDataManager& other); //代入演算子
    
};
#endif /* defined(__LastSupper__PlayerDataManager__) */
