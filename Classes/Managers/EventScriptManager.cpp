//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScriptManager.h"

// 唯一のインスタンスを初期化
static EventScriptManager* _instance = nullptr;

// インスタンスを生成&取得
EventScriptManager* EventScriptManager::getInstance(){
    if(!_instance) _instance = new EventScriptManager();
    return _instance;
}

// インスタンスの消去
void EventScriptManager::destroy(){
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
bool EventScriptManager::setJsonScript (string script)
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
        size_t offset = json.GetErrorOffset();
        ParseErrorCode code = json.GetParseError();
        const char* msg = GetParseError_En(code);
        printf("JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
        return false;
    } else {
        //jsonの値の取得テスト
        const rapidjson::Value& id = json["1"];
        const char* v = id["type"].GetString();
        printf("type = %s\n\n", v);
#ifdef DEBUG
        //テスト出力
        string json = "";
        ifstream filein(path);
        for (string line; getline(filein, line);)
        {
            //cout << line << endl;
            json += line;
        }
        cout << json << endl;
#endif
        return true;
    }
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