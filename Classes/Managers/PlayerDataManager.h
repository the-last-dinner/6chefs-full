//
//  PlayerDataManager.h
//  LastSupper
//
//  Created by Ryoya Ino on 2015/06/28.
//
//

#ifndef __LastSupper__PlayerDataManager__
#define __LastSupper__PlayerDataManager__

#include "define.h"

class CharacterData;
class StopWatch;

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

// 定数
private:
    static const int CHIKEN_SAVE_COUNT;
    static const int FAST_CLEAR_TIME;

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
    // Timer
    StopWatch* timer {nullptr};
    // ローカルセーブデータの存在の有無
    bool local_exist[MAX_SAVE_COUNT];

//通常関数
public:
    // グローバルセーブデータ処理
    void setGameEnd(const int end_id);
    
    // ローカルセーブデータ処理
    void setMainLocalData(const int id);
    vector<SaveIndex> getSaveList();
    int getSaveDataId();
    bool checkSaveDataExists(const int id);
    void save(const int id);

    // SET
    void setLocation(const Location& location, const int num = 0);
    void setLocation(const CharacterData& character, const int num = 0);
    void setLocation(const vector<CharacterData>& characters);
    void setFriendship(const int chara_id, const int level);
    void setEventNeverAgain(const int map_id, const int event_id, const bool flag = true);
    void setEventStatus(const int map_id, const int event_id, const int status);
    void setItem(const int item_id);
    void setItemEquipment(const Direction direction, const int item_id);
    void setChapterId(const int chapter_id);
    void setCharacterProfile(const int chara_id, const int level);
    void setPartyMember(const CharacterData& chara);
    void setToken();
    
    // REMOVE
    bool removeItem(const int item_id);
    bool removePartyMember(const int obj_id);
    
    // GET
    Location getLocation(const int num = 0);
    int getFriendship(const int chara_id);
    int getEventStatus(const int map_id, const int event_id);
    int getItem(const int item_id);
    map<int, int> getItemAll();
    int getItemEquipment(Direction direction);
    int getChapterId();
    int getCharacterProfileLevel(const int chara_id);
    CharacterData getPartyMember(const int num = 0);
    vector<CharacterData> getPartyMemberAll();
    int getPlayTimeSeconds();
    string getPlayTimeDisplay();
    string getPlayTimeDisplay(const int sec);
    int getSaveCount();
    int getBestSaveCount();
    int getBestClearTime();
    
    // CHECK
    bool checkItem(const int item_id);
    bool checkItemEquipment(const int item_id);
    bool checkFriendship(const int chara_id, const int val);
    bool checkChapterId(const int chapter_id);
    bool checkEventIsDone(const int map_id, const int event_id);
    bool checkEventStatus(const int map_id, const int event_id, const int status);
    bool checkTrophyhaving(const int trophy_id);
    bool checkNotExistToken(const string& token);
    bool isCleard();
    
private:
    // グローバルデータのセット
    bool setGlobalData();
    void saveGlobalData();
    // セーブデータを全初期化
    void initializeFiles();
    // JSONファイル読み込み
    rapidjson::Document readJsonFile(const string& path);
    // JSONファイル書き出し
    void writeJsonFile(const string& path, const rapidjson::Document& doc);
    //トロフィーセット
    void setTrophy(const int trophy_id);

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
