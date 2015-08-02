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
    //対象ローカルセーブデータid
    int local_id;
    //ローカルセーブデータ達
    rapidjson::Document local;
    //FileUtils
    cocos2d::FileUtils* fu;

//通常関数
public:
    //メインとなるローカルデータのセット
    void setMainLocalData(const int& id);
    //ローカルセーブデータリストの取得
    vector<SaveIndex> getSaveList();
    //セーブ
    void save(const int& id);
    /* flag管理系 */
    // SET
    void setFriendship(const string& character, const int& level);
    void setEventFlag(const string& map, const int& event_id, const bool& flag);
    void setItem(const int& item_id);
    void setItemEquipment(const int& which, const int& item_id);
    // GET
    int getFriendship(const string& character);
    bool getEventFlag(const string& map, const int& event_id);
    int getItem(const int& item_id);
    map<int, int> getItemAll();
    int getItemEquipment(const int& which);
    // CHECK
    bool checkItem(const int& item_id);
    bool checkItemEquipment(const int& item_id);
    bool checkFriendship(const string& character, const int& min);
    
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
