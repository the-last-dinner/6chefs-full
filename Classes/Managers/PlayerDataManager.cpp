//
//  PlayerDataManager.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/06/28.
//
//

#include "PlayerDataManager.h"

// 唯一のインスタンスを初期化
static PlayerDataManager* _instance = nullptr;

//セーブデータの個数
const int PlayerDataManager::MAX_SAVE_COUNT = 10;

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
{FUNCLOG}


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
        //グローバルセーブデータの読み込み
        this->setGlobalData();
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
    string path1 = fu->fullPathForFilename("save/global_template.json");
    // Create path of global save data
    string path2 = this->strReplace("global_template.json", "global.json", path1);
    // read global template data
    rapidjson::Document global_temp = this->readJsonFile(path1);
    // create global save data
    this->writeJsonFile(path2, global_temp);
    
    /* local save data */
    /*cout << "Create local save data." << endl;
    // Create path of local template
    string path3 = this->strReplace("global_template.json", "local_template.json", path1);
    // Read local template data
    rapidjson::Document local_temp = this->readJsonFile(path3);
    rapidjson::Value& temp = local_temp["0"];
    // Create empty local save data
    rapidjson::Document parent;
    const char* empty = R"({})";
    parent.Parse(empty);
    rapidjson::Value& child(parent);
    // Add local template
    child.AddMember("0", temp, parent.GetAllocator());
    // Initialize local save data
    this->writeJsonFile(this->strReplace("local_template.json", "local.json", path3), parent);
    */return;
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
    int minute;
    string time;
    for(int i=1; i<=MAX_SAVE_COUNT; i++){
        const char* cha_id = to_string(i).c_str();
        if(!this->global.HasMember(cha_id))
        {
            cout << "empty >> " << i << endl;
            //空のデータ
            save = SaveIndex(i, "--- NO DATA ---", "--時間--分", "  0", "---------------");
        } else {
            cout << "set >> " << i << endl;
            //プレイ時間を編集
            minute = this->global[cha_id]["play_time"].GetInt();
            time = this->getSprintf("%2s", to_string(minute / 60)) + "時間" + this->getSprintf("%2s", to_string(minute % 60)) + "分";
            //リスト生成
            save = SaveIndex(i, this->getSprintf("%15s", this
                                                   ->global[cha_id]["name"].GetString()), time, this->getSprintf("%3s", to_string(this->global[cha_id]["save_count"].GetInt())), this->getSprintf("%15s", this->global[cha_id]["map"].GetString()));
        }
        save_list.push_back(save);
    }
    return save_list;
}

//メインとなるローカルデータのidのセット
void PlayerDataManager::setMainLocalData(const int& id)
{
    FUNCLOG
    this->local_id = id;
    string file = (id == 0) ? "save/local_template.json": "save/local" + to_string(id) + ".json";
    string path = this->fu->fullPathForFilename(file);
    this->local = this->readJsonFile(path);
    return;
}

//セーブ
void PlayerDataManager::save(const int& id)
{
    FUNCLOG
    // save local
    string str_id = to_string(id);
    string path = this->fu->fullPathForFilename("save/local" + str_id + ".json");
    this->writeJsonFile(path, this->local);
    this->local_id = id;
    // save global
    const char* cha_id = str_id.c_str();
    if(this->global.HasMember(cha_id))
    {
        //セーブデータが存在する場合
        this->global[cha_id]["token"] = this->local["token"];
        this->global[cha_id]["name"] = this->local["name"];
        this->global[cha_id]["play_time"] = this->local["play_time"];
        this->global[cha_id]["save_count"] = this->local["save_count"];
        this->global[cha_id]["map"] = this->local["map"];
    } else {
        //セーブデータが存在しない場合
        rapidjson::Value empty(kObjectType);
        this->global.AddMember(StringRef(cha_id), empty, this->global.GetAllocator());
        this->global[cha_id].AddMember("token", this->local["token"], this->local.GetAllocator());
        this->global[cha_id].AddMember("name", this->local["name"], this->local.GetAllocator());
        this->global[cha_id].AddMember("play_time", this->local["play_time"], this->local.GetAllocator());
        this->global[cha_id].AddMember("save_count", this->local["save_count"], this->local.GetAllocator());
        this->global[cha_id].AddMember("map", this->local["map"], this->local.GetAllocator());
        
    }
    string path_g = this->fu->fullPathForFilename("save/global.json");
    this->writeJsonFile(path_g, this->global);
    return;
}

/* ******************************************************** *
 * ******************** Flag functions ******************** *
 * ******************************************************** */

/* SET */
//友好度のセット
void PlayerDataManager::setFriendship(const string& character, const int& level)
{
    FUNCLOG
    rapidjson::Value& friendship = this->local["friendship"];
    friendship[character.c_str()].SetInt(level);
    return;
}

//イベントフラグのセット
void PlayerDataManager::setEventFlag(const string& map, const int& event_id, const bool& flag)
{
    FUNCLOG
    rapidjson::Value& event = this->local["event"];
    rapidjson::Value::ConstMemberIterator itr = event.FindMember(map.c_str());
    //mapが存在するかチェック
    if(itr == event.MemberEnd()){
        event.AddMember(StringRef(map.c_str()), rapidjson::Value(), this->local.GetAllocator());
    }
    event = event[map.c_str()];
    //event_idが存在するかチェック
    const char* id = to_string(event_id).c_str();
    itr = event.FindMember(id);
    if(itr == event.MemberEnd()){
        event.AddMember(StringRef(id), rapidjson::Value(flag), this->local.GetAllocator());
    } else {
        event[id].SetBool(flag);
    }
    return;
}

//アイテムゲット時の処理
void PlayerDataManager::setItem(const int& item_id)
{
    FUNCLOG
    rapidjson::Value& item = this->local["item"];
    const char* id = to_string(item_id).c_str();
    rapidjson::Value::ConstMemberIterator itr = item.FindMember(id);
    int count = 0;
    if(itr != item.MemberEnd()){
        //既にゲットしているアイテムなら個数を+1する
        count = itr->value.GetInt();
        item[id].SetInt(count+1);
    } else {
        //初めてゲットしたアイテムならば新しい値をセット
        item.AddMember(StringRef(id), rapidjson::Value(1), this->local.GetAllocator());
    }
    return;
}

//アイテム装備時の処理
void PlayerDataManager::setItemEquipment(const int& which, const int& item_id)
{
    FUNCLOG
    rapidjson::Value& root = this->local;
    if(which == static_cast<int>(Direction::LEFT))
    {
        root["equipment_left"].SetInt(item_id);
    } else {
        root["equipment_right"].SetInt(item_id);
    }
    return;
}

/* GET */
//友好度の取得
int PlayerDataManager::getFriendship(const string& character)
{
    FUNCLOG
    return this->local["friendship"][character.c_str()].GetInt();
}

//イベントフラグの取得
bool PlayerDataManager::getEventFlag(const string& map, const int& event_id)
{
    FUNCLOG
    rapidjson::Value& event = this->local["event"];
    rapidjson::Value::ConstMemberIterator itr = event.FindMember(map.c_str());
    //mapが存在するかチェック
    if(itr == event.MemberEnd()){
        return false;
    }
    event = event[map.c_str()];
    //event_idが存在するかチェック
    const char* id = to_string(event_id).c_str();
    itr = event.FindMember(id);
    if(itr == event.MemberEnd()){
        return false;
    } else {
        return event[id].GetBool();
    }
}

//所持しているアイテムの取得
int PlayerDataManager::getItem(const int &item_id)
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
int PlayerDataManager::getItemEquipment(const int& which)
{
    FUNCLOG
    string key;
    key = (which == static_cast<int>(Direction::LEFT)) ? "equipment_left" : "equipment_right";
    return this->local[key.c_str()].GetInt();
}

/* CHECK */
//アイテムを1つ以上持っているかチェック
bool PlayerDataManager::checkItem(const int& item_id)
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
bool PlayerDataManager::checkItemEquipment(const int& item_id)
{
    FUNCLOG
    int right = this->getItemEquipment(static_cast<int>(Direction::RIGHT));
    int left = this->getItemEquipment(static_cast<int>(Direction::LEFT));
    if (item_id == right || item_id == left) {
        return true;
    } else{
        return false;
    }
}

//友好度が指定の値以上あるかどうか
bool PlayerDataManager::checkFriendship(const string& character, const int& min)
{
    FUNCLOG
    int level = this->getFriendship(character);
    if(level >= min){
        return true;
    } else {
        return false;
    }
}

/* ******************************************************** *
 * ******************** Util functions ******************** *
 * ******************************************************** */

// 文字列を置換する
string PlayerDataManager::strReplace(const string& pattern, const string& replacement, string target)
{
    std::string::size_type  Pos(target.find(pattern));
    while( Pos != std::string::npos )
    {
        target.replace( Pos, pattern.length(), replacement);
        Pos = target.find( pattern, Pos + replacement.length() );
    }
    return target;
}

//sprinfでformatした文字列を取得
string PlayerDataManager::getSprintf(const string& format, const string& str){
    char* c;
    sprintf(c, format.c_str(), str.c_str());
    return string(c);
}

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

