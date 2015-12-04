
//
//  PlayerDataManager.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/06/28.
/*
 [memo]
 ・セーブデータが選択されたらsetMainLocalData(int local_id)でlocalデータのセット
*/

#include "Managers/PlayerDataManager.h"
#include "Managers/CsvDataManager.h"

#include "Models/GlobalPlayerData.h"
#include "Models/LocalPlayerData.h"
#include "Models/StopWatch.h"

#include "Utils/StringUtils.h"
#include "Utils/JsonUtils.h"

#include "Datas/MapObject/CharacterData.h"

#pragma mark Initialize

// 唯一のインスタンスを初期化
static PlayerDataManager* _instance = nullptr;

// インスタンスを生成&取得
PlayerDataManager* PlayerDataManager::getInstance()
{
    if(!_instance) _instance = new PlayerDataManager();
    return _instance;
}

// インスタンスの消去
void PlayerDataManager::destroy()
{
    delete _instance;
    return;
}

//デストラクタ
PlayerDataManager::~PlayerDataManager()
{
    FUNCLOG
    CC_SAFE_RELEASE_NULL(this->timer);
    CC_SAFE_RELEASE_NULL(this->globalData);
}

// コンストラクタ
PlayerDataManager::PlayerDataManager()
{
    FUNCLOG
    //グローバルセーブデータの読み込み
    this->globalData = GlobalPlayerData::create();
    CC_SAFE_RETAIN(this->globalData);
}

#pragma mark -
#pragma mark GlobalSaveData


// グローバルセーブデータの初期化
void PlayerDataManager::initializeFiles()
{
    string global_temp_path = FileUtils::getInstance()->fullPathForFilename("save/global_template.json");
    
    /* local save data */
    rapidjson::Document local_init;
    local_init.SetObject();
    rapidjson::Value& status = local_init;
    // status:0(=空)のファイルを生成
    status.AddMember(StringRef("status"), rapidjson::Value(0), local_init.GetAllocator());
    string local_path = LastSupper::StringUtils::strReplace("global_template.json", "", global_temp_path);
    for(int i = 1; i <= MAX_SAVE_COUNT; i++){
        LastSupper::JsonUtils::writeJsonFile(local_path + "local" +  to_string(i) + ".json", local_init);
    }
    return;
}

// クリア時の処理
void PlayerDataManager::setGameEnd(const int end_id)
{
    // エンディングチェック
    int trophy_id;
    switch (end_id)
    {
        case 0:
            trophy_id = 6;
            break;
        case 1:
            trophy_id = 7;
            break;
        case 2:
            trophy_id = 8;
            break;
    }
    this->globalData->setTrophy(trophy_id);
    
    // セーブ回数チェック
    this->globalData->setBestSaveCount(this->getSaveCount());
    this->globalData->setBestClearTime(this->getPlayTimeSeconds());
    
    // トロコンチェック
    vector<int> trophies = CsvDataManager::getInstance()->getTrophyIdAll();
    int trophy_count {0};
    for(int trophy_id : trophies)
    {
        if (!this->globalData->hasTrophy(trophy_id)) trophy_count++;
    }
    if (trophy_count == trophies.size())
    {
        this->globalData->setTrophy(trophy_count);
    }
    
    this->globalData->setClearCount(this->local["token"].GetString());
    
    // グローバルデータをセーブ
    this->globalData->saveGlobalData();
}

#pragma mark -
#pragma mark LocalSaveData

// セーブデータのリスト表示用データ
vector<PlayerDataManager::SaveIndex> PlayerDataManager::getSaveList()
{
    FUNCLOG
    vector<PlayerDataManager::SaveIndex> save_list;
    SaveIndex save;
    // セーブデータを一つずつチェック
    for(int i=1; i<=MAX_SAVE_COUNT; i++){
        string file = "save/local" + to_string(i) + ".json";
        rapidjson::Document local = LastSupper::JsonUtils::readJsonFile(file.c_str());
        // status: 0>>セーブデータが存在しない, 1>>セーブデータが存在する
        if(local["status"].GetInt() == 0)
        {
            // セーブデータが存在しない
            cout << "empty >> " << i << endl;
            this->local_exist[i-1] = false;
            
            // 空のデータを生成
            save = SaveIndex(i, "--- NO DATA ---", "---------------", "  0", "00h00m00s");
            
        } else {
            // セーブデータが存在する
            cout << "set >> " << i << endl;
            this->local_exist[i-1] = true;
            
            // リスト生成
            save = SaveIndex(
                             i,
                             CsvDataManager::getInstance()->getChapterName(local["chapter"].GetInt()),
                             LastSupper::StringUtils::getSprintf("%15s", CsvDataManager::getInstance()->getMapName(local["map_id"].GetInt())),
                             this->getPlayTimeDisplay(local["play_time"].GetInt()),
                             LastSupper
                             ::StringUtils::getSprintf("%3s", to_string(local["save_count"].GetInt()))
                             );
        }
        save_list.push_back(save);
    }
    return save_list;
}

//メインとなるローカルデータのidのセット
void PlayerDataManager::setMainLocalData(const int id)
{
    FUNCLOG
    this->local_id = id;
    string file = (id == 0) ? "save/local_template.json": "save/local" + to_string(id) + ".json";
    string path = FileUtils::getInstance()->fullPathForFilename(file);
    this->local = LastSupper::JsonUtils::readJsonFile(path);
    // プレイ時間計測スタート
    this->timer = StopWatch::create(this->local["play_time"].GetInt());
    CC_SAFE_RETAIN(this->timer);
    this->timer->tic();
    return;
}

// メインとなるローカルデータのidを取得
int PlayerDataManager::getSaveDataId()
{
    return this->local_id;
}

//　表示用プレイ時間の取得
string PlayerDataManager::getPlayTimeDisplay(const int sec)
{
    int min = floor(sec / 60);
    int hour = floor(min / 60);
    string display = LastSupper::StringUtils::getSprintf("%02s", to_string(hour)) + "h" +LastSupper::StringUtils::getSprintf("%02s", to_string(min % 60)) + "m" + LastSupper::StringUtils::getSprintf("%02s", to_string(sec % 60))+ "s";
    return display;
}

// セーブ
void PlayerDataManager::save(const int id)
{
    FUNCLOG
    
    string str_id = to_string(id);
    
    // プレイ時間
    int playTime = this->getPlayTimeSeconds();
    if (playTime >= 360000)
    {
        playTime = 359999;
    }
    this->local["play_time"].SetInt(playTime);
    
    // セーブ回数更新
    int saveCnt = this->getSaveCount();
    if (saveCnt < 999)
    {
        this->local["save_count"].SetInt(saveCnt + 1);
    }
    
    // セーブ
    string path = "save/local" + str_id + ".json";
    LastSupper::JsonUtils::writeJsonFile(path, this->local);
    this->local_id = id;
    
    // グローバルデータのセーブ
    this->globalData->saveGlobalData();
    
    return;
}

// セーブデータの存在をチェック
bool PlayerDataManager::checkSaveDataExists(const int id)
{
    return this->local_exist[id - 1];
}

#pragma mark -
#pragma mark Setter

// オブジェクトの座標のセット
void PlayerDataManager::setLocation(const Location& location, const int num)
{
    if (num == 0) this->local["map_id"].SetInt(location.map_id);
    this->local["party"][num]["x"].SetInt(location.x);
    this->local["party"][num]["y"].SetInt(location.y);
    this->local["party"][num]["direction"].SetInt(static_cast<int>(location.direction));
    return;
}

void PlayerDataManager::setLocation(const CharacterData& character, const int num)
{
    this->setLocation(character.location, num);
}

void PlayerDataManager::setLocation(const vector<CharacterData>& characters)
{
    int chara_count = characters.size();
    for (int i = 0; i < chara_count; i++)
    {
        this->setLocation(characters[i], i);
    }
}

// 友好度のセット
void PlayerDataManager::setFriendship(const int chara_id, const int level)
{
    char cid_char[10];
    sprintf(cid_char, "%d", chara_id);
    this->local["friendship"][cid_char].SetInt(level);
    if (level >= 2)
    {
        this->globalData->setTrophy(chara_id);
    }
    return;
}

// イベントフラグのセット (イベントステータスへ変換 true>>1, false>>0)
void PlayerDataManager::setEventNeverAgain(const int map_id, const int event_id, const bool flag)
{
    // status取得
    int status {this->getEventStatus(map_id, event_id)};
    
    // statusを負の値にする
    if (status == 0 && flag)
    {
        status = -1; // 初回の場合
    }
    else if ( (status > 0 && flag) || (status < 0 && !flag) )
    {
        status = status * -1;
    }
    else
    {
        status = 1;
    }
    
    //　イベントステータスとしてセット
    this->setEventStatus(map_id, event_id, status);
}

// イベントステータスのセット
void PlayerDataManager::setEventStatus(const int map_id, const int event_id, const int status)
{
    char mid_char[10];
    sprintf(mid_char, "%d", map_id);
    rapidjson::Value mid  (kStringType);
    mid.SetString(mid_char, strlen(mid_char), this->local.GetAllocator());
    
    rapidjson::Value::ConstMemberIterator itr = this->local["event"].FindMember(mid_char);
    //mapが存在するかチェック
    if(itr == this->local["event"].MemberEnd()){
        this->local["event"].AddMember(mid, rapidjson::Value(kObjectType), this->local.GetAllocator());
    }
    //event_idが存在するかチェック
    char eid_char[10];
    sprintf(eid_char, "%d", event_id);
    rapidjson::Value eid (kStringType);
    eid.SetString(eid_char,strlen(eid_char),this->local.GetAllocator());
    itr = this->local["event"][mid_char].FindMember(eid_char);
    if(itr == this->local["event"][mid_char].MemberEnd()){
        this->local["event"][mid_char].AddMember(eid, rapidjson::Value(status), this->local.GetAllocator());
    } else {
        bool negative = itr->value.GetInt() < 0 ? true : false;
        int new_status = status < 0 ? status : (negative) ? status * -1 : status;
        this->local["event"][mid_char][eid_char].SetInt(new_status);
    }
    return;
}

// アイテムゲット時の処理
void PlayerDataManager::setItem(const int item_id)
{
    char iid_char[10];
    sprintf(iid_char, "%d", item_id);
    rapidjson::Value iid  (kStringType);
    iid.SetString(iid_char, strlen(iid_char), this->local.GetAllocator());
    
    rapidjson::Value::ConstMemberIterator itr = this->local["item"].FindMember(iid_char);
    int count = 0;
    if(itr != this->local["item"].MemberEnd()){
        //既にゲットしているアイテムなら個数を+1する
        count = itr->value.GetInt();
        this->local["item"][iid_char].SetInt(count+1);
    } else {
        //初めてゲットしたアイテムならば新しい値をセット
        this->local["item"].AddMember(iid, rapidjson::Value(1), this->local.GetAllocator());
    }
    return;
}

// アイテム装備時の処理
void PlayerDataManager::setItemEquipment(Direction direction, const int item_id)
{
    if(direction == Direction::LEFT)
    {
        this->local["equipment_left"].SetInt(item_id);
    }
    else
    {
        this->local["equipment_right"].SetInt(item_id);
    }
    return;
}

// chapterを切り替え
void PlayerDataManager::setChapterId(const int chapter_id)
{
    this->local["chapter"].SetInt(chapter_id);
}

// キャラクターのプロフィールを追加
void PlayerDataManager::setCharacterProfile(const int chara_id, const int level)
{
    char cid_char[10];
    sprintf(cid_char, "%d", chara_id);
    rapidjson::Value::ConstMemberIterator itr = this->local["chara"].FindMember(cid_char);
    if (itr != this->local["chara"].MemberEnd())
    {
        // すでに追加されているキャラクター
        this->local["chara"][cid_char].SetInt(level);
    }
    else
    {
        // 初めて追加するキャラ
        rapidjson::Value id (kStringType);
        id.SetString(cid_char,strlen(cid_char),this->local.GetAllocator());
        this->local["chara"].AddMember(id, rapidjson::Value(level), this->local.GetAllocator());
    }
}

// パーティメンバーを追加する
void PlayerDataManager::setPartyMember(const CharacterData& chara)
{
    
    rapidjson::Document member;
    member.SetObject();
    member.AddMember("chara_id", rapidjson::Value(chara.chara_id), this->local.GetAllocator());
    member.AddMember("obj_id", rapidjson::Value(chara.obj_id), this->local.GetAllocator());
    member.AddMember("x", rapidjson::Value(chara.location.x), this->local.GetAllocator());
    member.AddMember("y", rapidjson::Value(chara.location.y), this->local.GetAllocator());
    member.AddMember("direction", rapidjson::Value(static_cast<int>(chara.location.direction)), this->local.GetAllocator());
    this->local["party"].PushBack(member, this->local.GetAllocator());
}

// トークンをセットする
void PlayerDataManager::setToken()
{
    rapidjson::Value token(kStringType);
    string ranstr = LastSupper::StringUtils::getRandomString();
    CCLOG("TOKEN >>>>> %s", ranstr.c_str());
    this->local["token"].SetString(ranstr.c_str(), strlen(ranstr.c_str()), this->local.GetAllocator());
}

#pragma mark -
#pragma mark Remover

// アイテムを消費する
bool PlayerDataManager::removeItem(const int item_id)
{
    char iid_char[10];
    sprintf(iid_char, "%d", item_id);
    int count = this->getItem(item_id);
    if (count > 0)
    {
        // 所持数を-1
        this->local["item"][iid_char].SetInt(count - 1);
        // 右手を確認
        if(item_id == this->getItemEquipment(Direction::RIGHT))
        {
            this->setItemEquipment(Direction::RIGHT, 0);
        }
        // 左手を確認
        if (item_id == this->getItemEquipment(Direction::LEFT))
        {
            this->setItemEquipment(Direction::LEFT, 0);
        }
        return true;
    }
    return false;
}

// パーティメンバーを解除する
bool PlayerDataManager::removePartyMember(const int obj_id)
{
    bool isExsits = false;
    vector<CharacterData> members = this->getPartyMemberAll();
    int member_size = members.size();
    this->local["party"].Clear();
    this->local["party"].SetArray();
    for (int i = 0; i < member_size; i++)
    {
        if (members[i].obj_id == obj_id)
        {
            isExsits = true;
        }
        else
        {
            this->setPartyMember(members[i]);
        }
    }
    return isExsits;
}

#pragma mark -
#pragma mark Getter

// 主人公の位置をゲット
Location PlayerDataManager::getLocation(const int num)
{
    int map_id = this->local["map_id"].GetInt();
    rapidjson::Value& chara = this->local["party"][num];
    Location location(map_id, chara["x"].GetInt(), chara["y"].GetInt(), chara["direction"].GetInt());
    return location;
}

// 友好度の取得
int PlayerDataManager::getFriendship(const int chara_id)
{
    char cid_char[10];
    sprintf(cid_char, "%d", chara_id);
    rapidjson::Value::ConstMemberIterator itr = this->local["friendship"].FindMember(cid_char);
    if(itr != this->local["friendship"].MemberEnd()){
        return this->local["friendship"][cid_char].GetInt();
    } else {
        return -1;
    }
}

// イベントフラグの取得
int PlayerDataManager::getEventStatus(const int map_id, const int event_id)
{
    char mid_char[10];
    sprintf(mid_char, "%d", map_id);
    rapidjson::Value& event = this->local["event"];
    rapidjson::Value::ConstMemberIterator itr = event.FindMember(mid_char);
    //mapが存在するかチェック
    if(itr == event.MemberEnd()){
        return 0;
    }
    //event_idが存在するかチェック
    char eid_char[10];
    sprintf(eid_char, "%d", event_id);
    itr = event[mid_char].FindMember(eid_char);
    if(itr == event[mid_char].MemberEnd()){
        return 0;
    } else {
        return event[mid_char][eid_char].GetInt();
    }
}

// 所持しているアイテムの所持数を取得
int PlayerDataManager::getItem(const int item_id)
{
    rapidjson::Value& item = this->local["item"];
    char iid_char[10];
    sprintf(iid_char, "%d", item_id);
    rapidjson::Value::ConstMemberIterator itr = item.FindMember(iid_char);
    int count = 0;
    if(itr != item.MemberEnd()){
        count =  itr->value.GetInt();
    }
    return count;
}

// 所持しているアイテムをすべて取得
map<int, int> PlayerDataManager::getItemAll()
{
    map<int, int> items {};
    rapidjson::Value& item = this->local["item"];
    for(rapidjson::Value::ConstMemberIterator itr = item.MemberBegin();itr != item.MemberEnd(); itr++)
    {
        int item_id = stoi(itr->name.GetString());
        int count = itr->value.GetInt();
        if ( count > 0 )
        {
            items.insert({item_id, count});
        }
    }
    return items;
}

// 装備アイテムIDの取得
int PlayerDataManager::getItemEquipment(Direction direction)
{
    string key;
    key = (direction == Direction::LEFT) ? "equipment_left" : "equipment_right";
    return this->local[key.c_str()].GetInt();
}

// 現在のチャプターIDの取得
int PlayerDataManager::getChapterId()
{
    return this->local["chapter"].GetInt();
}

// キャラクターのプロフィール情報の見れるレベルを取得
int PlayerDataManager::getCharacterProfileLevel(const int chara_id)
{
    int level {-1}; // 存在しない場合は-1を返す
    char cid_char[10];
    sprintf(cid_char, "%d", chara_id);
    rapidjson::Value::ConstMemberIterator itr = this->local["chara"].FindMember(cid_char);
    if (itr != this->local["chara"].MemberEnd())
    {
        level = this->local["chara"][cid_char].GetInt();
    }
    return level;
}

// パーティメンバーを取得
CharacterData PlayerDataManager::getPartyMember(const int num)
{
    rapidjson::Value& chara = this->local["party"][num];
    Location location(this->local["map_id"].GetInt(), chara["x"].GetInt(), chara["y"].GetInt(), chara["direction"].GetInt());
    return CharacterData(chara["chara_id"].GetInt(), chara["obj_id"].GetInt(), location);
}

// パーティメンバーを全取得
vector<CharacterData> PlayerDataManager::getPartyMemberAll()
{
    vector<CharacterData> party {};
    int party_size = this->local["party"].Size();
    for (int i = 0; i < party_size; i++)
    {
        party.push_back(this->getPartyMember(i));
    }
    return party;
}

// 現在のプレイ時間の表示用を取得
string PlayerDataManager::getPlayTimeDisplay()
{
    return this->getPlayTimeDisplay(this->getPlayTimeSeconds());
}

// プレイ時間を秒で取得
int PlayerDataManager::getPlayTimeSeconds()
{
    return this->timer->getTimeInt();;
}

// セーブ回数を取得
int PlayerDataManager::getSaveCount()
{
    return this->local["save_count"].GetInt();
}





#pragma mark -
#pragma mark Checker

// アイテムを1つ以上持っているかチェック
bool PlayerDataManager::checkItem(const int item_id)
{
    int count = this->getItem(item_id);
    if (count > 0) {
        return true;
    } else {
        return false;
    }
}

// アイテムを装備しているかチェック
bool PlayerDataManager::checkItemEquipment(const int item_id)
{
    int right = this->getItemEquipment(Direction::RIGHT);
    int left = this->getItemEquipment(Direction::LEFT);
    if (item_id == right || item_id == left) {
        return true;
    } else{
        return false;
    }
}

// 友好度が指定の値と一致するか
bool PlayerDataManager::checkFriendship(const int chara_id, const int val)
{
    int level = this->getFriendship(chara_id);
    if(level == val){
        return true;
    } else {
        return false;
    }
}

// チャプターIDが指定のIDと一致するか
bool PlayerDataManager::checkChapterId(const int chapter_id)
{
    if(chapter_id == this->getChapterId())
    {
        return true;
    } else {
        return false;
    }
}

// イベントを見たかどうか
bool PlayerDataManager::checkEventIsDone(const int map_id, const int event_id)
{
    int status = this->getEventStatus(map_id, event_id);
    return status < 0 ? true : false;
}

// イベントステータスが指定の値かどうか
bool PlayerDataManager::checkEventStatus(const int map_id, const int event_id, const int status)
{
    return status == abs(this->getEventStatus(map_id, event_id)) ? true : false;
}

GlobalPlayerData* PlayerDataManager::getGlobalData() const
{
    return this->globalData;
}