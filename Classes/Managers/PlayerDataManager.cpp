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
    //
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
    cout << "Create local save data." << endl;
    // Create path of local template
    string path3 = this->strReplace("global_template.json", "local_template.json", path1);
    // read local template data
    rapidjson::Document local_temp = this->readJsonFile(path3);
    // create local save data
    string path4;
    for(int i=1; i<=MAX_SAVE_COUNT; i++)
    {
        path4 = this->strReplace("local_template.json", "local"+to_string(i)+".json", path3);
        this->writeJsonFile(path4, local_temp);
    }
    return;
}

/* ******************************************************** *
 * ******************* Normal functions ******************* *
 * ******************************************************** */

//全ローカルセーブデータの呼び出し
void PlayerDataManager::setLocalDataAll()
{
    FUNCLOG
    this->local.clear();
    string temp = "save/local";
    string path;
    for(int i=1;i<=MAX_SAVE_COUNT; i++)
    {
        path = this->fu->fullPathForFilename(temp + to_string(i) + ".json");
        this->local.push_back(readJsonFile(path));
        //this->local.push_back((path == "") ? nullptr : readJsonFile(path));
    }
    return;
}

//セーブデータのリスト表示用データ
vector<PlayerDataManager::SaveIndex> PlayerDataManager::getSaveList()
{
    FUNCLOG
    vector<PlayerDataManager::SaveIndex> save_list;
    SaveIndex save;
    int minute;
    string time;
    for(int i=0; i<MAX_SAVE_COUNT; i++){
        // 本当はいちいち初期化したくないけどしゃあなし
        rapidjson::Document doc(&this->local.at(i).GetAllocator());
        rapidjson::Value& token = doc["token"];
        if(token.IsNull())
        {
            //空のデータ
            save = SaveIndex(i+1, "--- NO DATA ---", "--時間--分", "  0", "---------------");
        } else {
            //プレイ時間を編集
            minute = doc["play_time"].GetInt();
            time = this->getSprintf("%2s", to_string(minute / 60)) + "時間" + this->getSprintf("%2s", to_string(minute % 60)) + "分";
            //リスト生成
            save = SaveIndex(i+1, this->getSprintf("%15s", doc["name"].GetString()), time, this->getSprintf("%3s", to_string(doc["save_count"].GetInt())), this->getSprintf("%15s", doc["map"].GetString()));
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
    return;
}

//セーブ
void PlayerDataManager::save(const int& id)
{
    FUNCLOG
    // save local
    string path_l = this->fu->fullPathForFilename(("save/local" + to_string(id)) + ".json");
    this->writeJsonFile(path_l, this->local.at(this->local_id));
    this->local[id] = this->readJsonFile(path_l);
    this->local_id = id;
    // save local
    string path_g = this->fu->fullPathForFilename(("save/global.json"));
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
    rapidjson::Value& friendship = this->local[this->local_id]["friendship"];
    friendship[character.c_str()].SetInt(level);
    return;
}

//イベントフラグのセット
void PlayerDataManager::setEventFlag(const string& map, const int& event_id, const bool& flag)
{
    FUNCLOG
    rapidjson::Value& event = this->local[this->local_id]["event"];
    rapidjson::Value::ConstMemberIterator itr = event.FindMember(map.c_str());
    //mapが存在するかチェック
    if(itr == event.MemberEnd()){
        event.AddMember(StringRef(map.c_str()), rapidjson::Value(), this->local[this->local_id].GetAllocator());
    }
    event = event[map.c_str()];
    //event_idが存在するかチェック
    const char* id = to_string(event_id).c_str();
    itr = event.FindMember(id);
    if(itr == event.MemberEnd()){
        event.AddMember(StringRef(id), rapidjson::Value(flag), this->local[this->local_id].GetAllocator());
    } else {
        event[id].SetBool(flag);
    }
    return;
}

//アイテムゲット時の処理
void PlayerDataManager::setItem(const int& item_id)
{
    FUNCLOG
    rapidjson::Value& item = this->local[this->local_id]["item"];
    const char* id = to_string(item_id).c_str();
    rapidjson::Value::ConstMemberIterator itr = item.FindMember(id);
    int count = 0;
    if(itr != item.MemberEnd()){
        //既にゲットしているアイテムなら個数を+1する
        count = itr->value.GetInt();
        item[id].SetInt(count+1);
    } else {
        //初めてゲットしたアイテムならば新しい値をセット
        item.AddMember(StringRef(id), rapidjson::Value(1), this->local[this->local_id].GetAllocator());
    }
    return;
}

//アイテム装備時の処理
void PlayerDataManager::setItemEquipment(const int& which, const int& item_id)
{
    FUNCLOG
    rapidjson::Value& root = this->local[this->local_id];
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
    return this->local[this->local_id]["friendship"][character.c_str()].GetInt();
}

//イベントフラグの取得
bool PlayerDataManager::getEventFlag(const string& map, const int& event_id)
{
    FUNCLOG
    rapidjson::Value& event = this->local[this->local_id]["event"];
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
    rapidjson::Value& item = this->local[this->local_id]["item"];
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
    rapidjson::Value& item = this->local[this->local_id]["item"];
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
    return this->local[this->local_id][key.c_str()].GetInt();
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
    } else {
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

