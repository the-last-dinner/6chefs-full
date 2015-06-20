//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScriptManager.h"

//EventTypeのmap
const map<string, int> EventScriptManager::EventType = {
    //命令タイプ
    {"sequence", 1},    //順番に処理を実行
    {"spawn", 2},       //同時に処理を実行
    {"flag", 3},        //flagによって場合分けして実行
    //イベントタイプ
    {"move", 1001},     //オブジェクトの移動
    {"talk", 1002},     //キャラクターの会話
    {"message", 1003},  //システムのメッセージ
    {"changeMap", 1004},//マップ移動
    {"fade", 1005},     //画面特殊効果
    {"playSE", 1006},   //効果音再生
    {"playBGM", 1007},  //BGM再生
    {"control", 1008},  //操作状態の変更
    {"read", 1009}      //書物読んでるモード
};

// 唯一のインスタンスを初期化
static EventScriptManager* _instance = nullptr;

// インスタンスを生成&取得
EventScriptManager* EventScriptManager::getInstance()
{
    if(!_instance) _instance = new EventScriptManager();
    return _instance;
}

// インスタンスの消去
void EventScriptManager::destroy()
{
    delete _instance;
    return;
}

// コンストラクタ
EventScriptManager::EventScriptManager():fu(FileUtils::getInstance())
{FUNCLOG}

// デストラクタ
EventScriptManager::~EventScriptManager()
{FUNCLOG}

//イベントスクリプトファイルの読み込み
bool EventScriptManager::setEventScript (string script)
{
    FUNCLOG
    FILE* fp;
    char buf[512];
    //ファイルパス
    string path = fu->fullPathForFilename("event/" +script + ".json");
    const char* cstr = path.c_str();
    //JSONファイルを読み込んでインスタンス変数jsonに格納
    fp = fopen(cstr, "rb");
    FileReadStream rs(fp, buf, sizeof(buf));
    json.ParseStream(rs);
    fclose(fp);
    //JSONの文法エラーチェック
    bool error = json.HasParseError();
    if(error){
        //エラーがあった場合
        size_t offset = json.GetErrorOffset();
        ParseErrorCode code = json.GetParseError();
        const char* msg = GetParseError_En(code);
        printf("JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
        return false;
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
        //マップ初期化イベント(0番)呼び出し
        vector<int> spid;
        vector<Sprite*> sprite;
        bool success = runEvent(0, spid, sprite);
        return success;
    }
}

//イベントIDからイベントを実行
bool EventScriptManager::runEvent(int id, vector<int> spid, vector<Sprite*> sprite)
{
    //idをint型からchar*に変換
    string sid = to_string(id);
    const char* csid = sid.c_str();
    //JsonEventScriptのidから命令
    rapidjson::Value& event = json[csid];
    string type = static_cast<string>(event["type"].GetString());
    printf("\nevent_id:%d\ntype = %s\n\n", id, type.c_str());
    //各命令の処理
    dealScript(&event, spid, sprite);
    return true;
}

//各イベント命令処理の場合分け
bool EventScriptManager::dealScript(rapidjson::Value* event, vector<int> spid, vector<Sprite*> sprite)
{
    //string type = static_cast<string>(event["type"].GetString());
    //int etid = EventType.at(type);
    //cout << "type>>" << type << endl;
    /*switch (etid){
        case EventType.at("sequence"):
        break;
        case EventType.at("spawn"):
        break;
        default: ;
    }*/
}

//文字列のトリミング
string EventScriptManager::trim(const string& string, const char* trimCharacterList = " \t\v\r\n")
{
    FUNCLOG
    std::string result;
    // 左側からトリムする文字以外が見つかる位置を検索します。
    string::size_type left = string.find_first_not_of(trimCharacterList);
    if (left != string::npos)
    {
        // 左側からトリムする文字以外が見つかった場合は、同じように右側からも検索します。
        string::size_type right = string.find_last_not_of(trimCharacterList);
        // 戻り値を決定します。ここでは右側から検索しても、トリムする文字以外が必ず存在するので判定不要です。
        result = string.substr(left, right - left + 1);
    }
    return result;
}