//
//  PlayerDataManager.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/06/28.
/*
 [memo]
 ・オブジェクト生成時にコンストラクタでグローバルセーブデータの読込(初回時は作成)
 ・セーブデータ選択が開かれる時にgetSaveIndexからセーブデータ表示用構造体を取得
 ・セーブデータが選択されたらsetMainLocalData(int local_id)でlocalデータのセット
*/

#include "Managers/PlayerDataManager.h"
#include "Managers/CsvDataManager.h"
#include "Utils/StringUtils.h"

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
PlayerDataManager::~PlayerDataManager(){FUNCLOG}


/* ******************************************************** *
 * ******************** Init functions ******************** *
 * ******************************************************** */

//コンストラクタ
PlayerDataManager::PlayerDataManager():fu(FileUtils::getInstance())
{
    FUNCLOG
    //グローバルセーブデータの読み込み
    if(!this->setGlobalData())
    {
        //セーブデータの初期作成
        this->initializeFiles();
    }
}

//グローバルデータの読み込み
bool PlayerDataManager::setGlobalData()
{
    FUNCLOG
    //ファイルパス
    string path = this->fu->fullPathForFilename("save/global.json");
    if(path == "")
    {
        cout << "Global save data is missing." << endl;
        return false;
    }
    //global.jsonを読み込んでインスタンス変数globalに格納
    this->global = this->readJsonFile(path);
    return true;
}

//グローバルセーブデータの初期化
void PlayerDataManager::initializeFiles()
{
    FUNCLOG
    /* global save data */
    cout << "Create global save data." << endl;
    // Get path of global template
    string global_temp_path = fu->fullPathForFilename("save/global_template.json");
    // Create path of global save data
    string global_path = LastSupper::StringUtils::strReplace("global_template.json", "global.json", global_temp_path);
    // read global template data
    rapidjson::Document global_temp = this->readJsonFile(global_temp_path);
    // create global save data
    this->writeJsonFile(global_path, global_temp);
    // set global save data
    this->global = readJsonFile(global_path);
    
    /* local save data */
    rapidjson::Document local_init;
    local_init.SetObject();
    rapidjson::Value& status = local_init;
    // status:0(=空)のファイルを生成
    status.AddMember(StringRef("status"), rapidjson::Value(0), local_init.GetAllocator());
    string local_path = LastSupper::StringUtils::strReplace("global_template.json", "", global_temp_path);
    for(int i = 1; i <= MAX_SAVE_COUNT; i++){
        this->writeJsonFile(local_path + "local" +  to_string(i) + ".json", local_init);
    }
    return;
}

/* ******************************************************** *
 * ******************* Normal functions ******************* *
 * ******************************************************** */

//セーブデータのリスト表示用データ
vector<PlayerDataManager::SaveIndex> PlayerDataManager::getSaveList()
{
    FUNCLOG
    vector<PlayerDataManager::SaveIndex> save_list;
    SaveIndex save;
    int sec, min;
    string time;
    // セーブデータを一つずつチェック
    for(int i=1; i<=MAX_SAVE_COUNT; i++){
        string file = "save/local" + to_string(i) + ".json";
        rapidjson::Document local = this->readJsonFile(file.c_str());
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
            
            // プレイ時間
            sec = local["play_time"].GetInt();
            min = sec / 60;
            time = LastSupper::StringUtils::getSprintf("%02s", to_string(min/60)) + "h" +LastSupper::StringUtils::getSprintf("%02s", to_string(min)) + "m" + LastSupper::StringUtils::getSprintf("%02s", to_string(sec % 60))+ "s";
            
            // リスト生成
            save = SaveIndex(
                             i,
                             CsvDataManager::getInstance()->getChapterName(local["chapter"].GetInt()),
                             LastSupper::StringUtils::getSprintf("%15s", CsvDataManager::getInstance()->getMapName(local["location"][0].GetInt())),
                             time,
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
    string path = this->fu->fullPathForFilename(file);
    this->local = this->readJsonFile(path);
    // プレイ時間計測スタート
    this->start_time_ms = this->getSec();
    return;
}

// メインとなるローカルデータのidを取得
int PlayerDataManager::getSaveDataId()
{
    FUNCLOG
    return this->local_id;
}

// 時間取得
double PlayerDataManager::getSec(){
    timeval tv;
    gettimeofday(&tv, nullptr);
    return (tv.tv_sec) + (tv.tv_usec) * 1e-6;
}

// プレイ時間を秒で取得し、スタート時間のリセット
int PlayerDataManager::getPlayTimeSeconds()
{
    // 計測時間の管理
    double start = this->start_time_ms;
    double stop = this->getSec();
    // 計測処理
    int interval_time = (int)(stop - start);
    // 開始時間を再設定
    this->start_time_ms = this->getSec();
    // プレイ時間を格納
    return (this->local["play_time"].GetInt() + interval_time);
}

//セーブ
void PlayerDataManager::save(const int id)
{
    FUNCLOG
    // save local
    string str_id = to_string(id);
    this->local["play_time"].SetInt(this->getPlayTimeSeconds());
    this->local["datetime"].SetInt(this->getSec());
    this->local["save_count"].SetInt(this->local["save_count"].GetInt() + 1);
    PlayerDataManager::Location loc = this->getLocation();
    this->local["location"][0].SetInt(loc.map_id);
    this->local["location"][1].SetInt(loc.x);
    this->local["location"][2].SetInt(loc.y);
    this->local["location"][3].SetInt(static_cast<int>(loc.direction));
    string path = "save/local" + str_id + ".json";
    this->writeJsonFile(path, this->local);
    this->local_id = id;
    // キャプチャースクリーンの保存
    string path_s = LastSupper::StringUtils::strReplace("global.json", "screen" + to_string(id)+ ".png", fu->FileUtils::fullPathForFilename("save/global.json"));
    utils::captureScreen([=](bool success, string filename){
        if(success)
        {
            // cache削除
            Director::getInstance()->getTextureCache()->removeTextureForKey(filename);
        }
    }, path_s);
    return;
}

// セーブデータの存在をチェック
bool PlayerDataManager::checkSaveDataExists(const int id)
{
    FUNCLOG
    //return (this->fu->isFileExist("save/local" + to_string(id) + ".json")) ? true : false;
    return this->local_exist[id - 1];
}

/* ******************************************************** *
 * ******************** Flag functions ******************** *
 * ******************************************************** */

/* SET */
//主人公の座標のセット
void PlayerDataManager::setLocation(const Location& location)
{
    FUNCLOG
    // 配列を削除
    this->local["location"].Clear();
    // 配列をセット
    this->local["location"].SetArray();
    this->local["location"].PushBack(location.map_id, this->local.GetAllocator());
    this->local["location"].PushBack(location.x, this->local.GetAllocator());
    this->local["location"].PushBack(location.y, this->local.GetAllocator());
    this->local["location"].PushBack(static_cast<int>(location.direction), this->local.GetAllocator());
    return;
}

//友好度のセット
void PlayerDataManager::setFriendship(const string& character, const int level)
{
    FUNCLOG
    this->local["friendship"][character.c_str()].SetInt(level);
    return;
}

//イベントフラグのセット
void PlayerDataManager::setEventFlag(const int map_id, const int event_id, const bool& flag)
{
    FUNCLOG
    const char* mid_char = to_string(map_id).c_str();
    char buff[50];
    sprintf(buff, "%d", map_id);
    rapidjson::Value mid  (kStringType);
    mid.SetString(buff, strlen(buff), this->local.GetAllocator());
    
    rapidjson::Value::ConstMemberIterator itr = this->local["event"].FindMember(mid_char);
    //mapが存在するかチェック
    if(itr == this->local["event"].MemberEnd()){
        this->local["event"].AddMember(mid, rapidjson::Value(), this->local.GetAllocator());
        this->local["event"][mid_char].SetObject();
    }
    //event_idが存在するかチェック
    const char* id_char = to_string(event_id).c_str();
    sprintf(buff, "%d", event_id);
    rapidjson::Value id (kStringType);
    id.SetString(buff,strlen(buff),this->local.GetAllocator());
    itr = this->local["event"][mid_char].FindMember(id_char);
    if(itr == this->local["event"][mid_char].MemberEnd()){
        this->local["event"][mid_char].AddMember(id, rapidjson::Value(flag), this->local.GetAllocator());
    } else {
        this->local["event"][mid_char][id_char].SetBool(flag);
    }
    return;
}

//アイテムゲット時の処理
void PlayerDataManager::setItem(const int item_id)
{
    FUNCLOG
    const char* id_char = to_string(item_id).c_str();
    char buff[50];
    sprintf(buff, "%d", item_id);
    rapidjson::Value id  (kStringType);
    id.SetString(buff, strlen(buff), this->local.GetAllocator());
    
    rapidjson::Value::ConstMemberIterator itr = this->local["item"].FindMember(id);
    int count = 0;
    if(itr != this->local["item"].MemberEnd()){
        //既にゲットしているアイテムなら個数を+1する
        count = itr->value.GetInt();
        this->local["item"][id_char].SetInt(count+1);
    } else {
        //初めてゲットしたアイテムならば新しい値をセット
        this->local["item"].AddMember(id, rapidjson::Value(1), this->local.GetAllocator());
    }
    return;
}

//アイテム装備時の処理
void PlayerDataManager::setItemEquipment(Direction direction, const int item_id)
{
    FUNCLOG
    if(direction == Direction::LEFT)
    {
        this->local["equipment_left"].SetInt(item_id);
    } else {
        this->local["equipment_right"].SetInt(item_id);
    }
    return;
}

// chapterを切り替え
void PlayerDataManager::setChapterId(const int chapter_id)
{
    FUNCLOG
    this->local["chapter"].SetInt(chapter_id);
    return;
}

/* GET */
//主人公の位置をゲット
PlayerDataManager::Location PlayerDataManager::getLocation()
{
    FUNCLOG
    rapidjson::Value& loc = this->local["location"];
    PlayerDataManager::Location location(loc[0].GetInt(), loc[1].GetInt(), loc[2].GetInt(), loc[3].GetInt());
    return location;
}

//友好度の取得
int PlayerDataManager::getFriendship(const string& character)
{
    FUNCLOG
    return this->local["friendship"][character.c_str()].GetInt();
}

//イベントフラグの取得
bool PlayerDataManager::getEventFlag(const int map_id, const int event_id)
{
    FUNCLOG
    const char* mid = to_string(map_id).c_str();
    rapidjson::Value& event = this->local["event"];
    rapidjson::Value::ConstMemberIterator itr = event.FindMember(mid);
    //mapが存在するかチェック
    if(itr == event.MemberEnd()){
        return false;
    }
    //event_idが存在するかチェック
    const char* id = to_string(event_id).c_str();
    itr = event[mid].FindMember(id);
    if(itr == event[mid].MemberEnd()){
        return false;
    } else {
        return event[mid][id].GetBool();
    }
}

//所持しているアイテムの取得
int PlayerDataManager::getItem(const int item_id)
{
    FUNCLOG
    rapidjson::Value& item = this->local["item"];
    const char* id = to_string(item_id).c_str();
    rapidjson::Value::ConstMemberIterator itr = item.FindMember(id);
    int count = 0;
    if(itr != item.MemberEnd()){
        count =  itr->value.GetInt();
    }
    return count;
}

//所持しているアイテムの取得
map<int, int> PlayerDataManager::getItemAll()
{
    FUNCLOG
    map<int, int> items;
    rapidjson::Value& item = this->local["item"];
    for(rapidjson::Value::ConstMemberIterator itr = item.MemberBegin();itr != item.MemberEnd(); itr++)
    {
        int item_id = stoi(itr->name.GetString());
        int count = itr->value.GetInt();
        items.insert({item_id, count});
    }
    return items;
}

//装備アイテムIDの取得
int PlayerDataManager::getItemEquipment(Direction direction)
{
    FUNCLOG
    string key;
    key = (direction == Direction::LEFT) ? "equipment_left" : "equipment_right";
    return this->local[key.c_str()].GetInt();
}

// 現在のチャプターIDの取得
int PlayerDataManager::getChapterId()
{
    FUNCLOG
    return this->local["chapter"].GetInt();
}

/* CHECK */
//アイテムを1つ以上持っているかチェック
bool PlayerDataManager::checkItem(const int item_id)
{
    FUNCLOG
    int count = this->getItem(item_id);
    if (count > 0) {
        return true;
    } else {
        return false;
    }
}

//アイテムを装備しているかチェック
bool PlayerDataManager::checkItemEquipment(const int item_id)
{
    FUNCLOG
    int right = this->getItemEquipment(Direction::RIGHT);
    int left = this->getItemEquipment(Direction::LEFT);
    if (item_id == right || item_id == left) {
        return true;
    } else{
        return false;
    }
}

//友好度が指定の値と一致するか
bool PlayerDataManager::checkFriendship(const string& character, const int val)
{
    FUNCLOG
    int level = this->getFriendship(character);
    if(level == val){
        return true;
    } else {
        return false;
    }
}

//チャプターIDが指定のIDと一致するか
bool PlayerDataManager::checkChapterId(const int chapter_id)
{
    FUNCLOG
    if(chapter_id == this->getChapterId())
    {
        return true;
    } else {
        return false;
    }
}

/* ******************************************************** *
 * ******************** Util functions ******************** *
 * ******************************************************** */

// 絶対パスからjsonファイルの取得
rapidjson::Document PlayerDataManager::readJsonFile(const string& path)
{
    FUNCLOG
    cout << "Read json file. path>>" << path << endl;
    const char* cpath = path.c_str();
    rapidjson::Document doc;
    FILE* fp;
    char buf[512];
    fp = fopen(cpath, "rb");
    FileReadStream rs(fp, buf, sizeof(buf));
    doc.ParseStream(rs);
    fclose(fp);
    //構文エラー判定
    bool error = doc.HasParseError();
    if(error){
        //エラーがあった場合
        size_t offset = doc.GetErrorOffset();
        ParseErrorCode code = doc.GetParseError();
        const char* msg = GetParseError_En(code);
        printf("GlobalTemplate JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
        return nullptr;
    } else {
        //エラーがなかった場合
#ifdef DEBUG
        //テスト出力
        ifstream filein(path);
        for (string line; getline(filein, line);)
        {
            cout << line << endl;
        }
#endif
        return doc;
    }
}

// JsonFile書き出し
void PlayerDataManager::writeJsonFile(const string &path, const rapidjson::Document& doc)
{
    FUNCLOG
    cout << "Write json file. path>>" << path << endl;
    const char* cpath = path.c_str();
    FILE* fp;
    char buf[512];
    // write
    fp = fopen(cpath, "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));
    Writer<FileWriteStream> writerf(ws);
    doc.Accept(writerf);
    fclose(fp);
    return;
}

