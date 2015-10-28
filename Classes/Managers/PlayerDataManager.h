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
        int data_id {0};
        string chapter {};
        string map_name {};
        string play_time {};
        string save_count {};
        SaveIndex(int i, const string& chap, const string& mn, const string& pt, const string& sc):data_id(i), chapter(chap), map_name(mn), play_time(pt), save_count(sc){};
        SaveIndex(){};
    };
    struct Location
    {
        int map_id{0};
        int x {0};
        int y {0};
        Direction direction {Direction::SIZE};
        Location(int map_id, int x, int y, int direction):map_id(map_id), x(x), y(y), direction(static_cast<Direction>(direction)){};
        Location(int map_id, int x, int y, Direction direction):map_id(map_id), x(x), y(y), direction(direction){};
        Location(){};
    };

//インスタンス変数
private:
    // グローバルセーブデータ
    rapidjson::Document global;
    // ローカルセーブデータ
    rapidjson::Document local;
    // 対象ローカルセーブデータid
    int local_id {0};
    // FileUtils
    cocos2d::FileUtils* fu;
    // 時間計測開始時間(単位:ms)
    double start_time_ms {0};
    // ローカルセーブデータの存在の有無
    bool local_exist[MAX_SAVE_COUNT];

//通常関数
public:
    //メインとなるローカルデータのセット
    void setMainLocalData(const int id);
    //ローカルセーブデータリストの取得
    vector<SaveIndex> getSaveList();
    //セーブ
    void save(const int id);
    // セーブデータが存在するかチェック
    bool checkSaveDataExists(const int id);
    // セーブデータIDの取得
    int getSaveDataId();
    // プレイ時間の取得
    int getPlayTimeSeconds();
    // 時間取得
    double getSec();
    /* flag管理系 */
    // SET
    void setLocation(const Location& location);
    void setFriendship(const string& character, const int level);
    void setEventFlag(const int map_id, const int event_id, const bool& flag);
    void setItem(const int item_id);
    void setItemEquipment(const Direction direction, const int item_id);
    void setChapterId(const int chapter_id);
    // GET
    Location getLocation();
    int getFriendship(const string& character);
    bool getEventFlag(const int map_id, const int event_id);
    int getItem(const int item_id);
    map<int, int> getItemAll();
    int getItemEquipment(Direction direction);
    int getChapterId();
    // CHECK
    bool checkItem(const int item_id);
    bool checkItemEquipment(const int item_id);
    bool checkFriendship(const string& character, const int val);
    bool checkChapterId(const int chapter_id);
private:
    //グローバルデータのセット
    bool setGlobalData();
    //セーブデータを全初期化
    void initializeFiles();
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
