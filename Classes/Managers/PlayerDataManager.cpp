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
    /*StringBuffer s;
#if 1
    Writer<StringBuffer> writer(s);
#else
    PrettyWriter<StringBuffer> writer(s);
    writer.SetIndent('\t', 1);
#endif
    
    writer.StartObject();
    
    writer.Key("id");
    writer.String("global_id");
    
    writer.Key("obj");
    writer.StartObject();
    writer.Key("level");
    writer.Int(82);
    writer.EndObject();
    
    writer.EndObject();
    
    const char* result = s.GetString();
    printf("%s\n", result);
    */
    //fileStream代入用
    //const char* json = R"({"id":"global_id", "level":88})";
    //rapidjson::Document doc;
    
    // 文字列のjsonをrapidjsonのオブジェクトへ変換
    //StringStream ss(json);
    //doc.ParseStream(ss);

    /*FILE *fp1;
    fp1 = fopen("/Users/Ryoya/Source/Xcode/LastSupper/Resources/save/test.dat", "wb");
    fprintf(fp1, "aiueo");
    fclose(fp1);*/
    
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

//友好度のセット
void PlayerDataManager::setFriendship(const string& character, const int& level)
{
    FUNCLOG
    rapidjson::Value& friendship = this->local[this->local_id]["friendship"];
    friendship[character.c_str()].SetInt(level);
    return;
}

//イベントフラグのセット
void PlayerDataManager::setEventFlag(const string& map, const int& event_id)
{
    FUNCLOG
    rapidjson::Value& event = this->local[this->local_id]["event"][map.c_str()];
    event[to_string(event_id).c_str()].SetBool(true);
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
        count = itr->value.GetInt();
    } else {
        item.AddMember(StringRef(id), rapidjson::Value(1), this->local[this->local_id].GetAllocator());
    }
    item.SetInt(count+1);
    return;
}

//アイテム装備時の処理
void PlayerDataManager::setItemEquipment(const int& which, const int& item_id)
{
    FUNCLOG
    rapidjson::Value& item = this->local[this->local_id]["item"];
    int eq_id = 0;
    eq_id = item["equipment_right"].GetInt();
    return;
}

//友好度の取得
int PlayerDataManager::getFriendship(const string& character)
{
    FUNCLOG
    rapidjson::Value& friendship = this->local[this->local_id]["friendship"];
    return friendship[character.c_str()].GetInt();
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

