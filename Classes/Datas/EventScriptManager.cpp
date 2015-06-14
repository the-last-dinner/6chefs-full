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

// コンストラクタ
EventScriptManager::EventScriptManager():fu(FileUtils::getInstance())
{
    FUNCLOG
    
}

// デストラクタ
EventScriptManager::~EventScriptManager()
{FUNCLOG}

//イベントスクリプトファイルの読み込み
void EventScriptManager::readJsonScript ()
{
    FUNCLOG
    string script = "TestScript.txt"; //イベントスクリプトファイル名
    string path = fu->fullPathForFilename(script); //絶対パス取得
    string json = "";
    //一行ずつスクリプトファイルの読み込み
    ifstream filein(path);
    for (string line; getline(filein, line);)
    {
        //cout << line << endl;
        json += line;
    }
    //テスト出力
#ifdef DEBUG
    cout << json << endl;
#endif
    //jsonテキストを変換
    jsonToMap(json);
    return;
}

//与えられたjsonテキストを
void EventScriptManager::jsonToMap(string json){
    FUNCLOG
    FILE* fp;
    char buf[512];
    //"/Users/Ryoya/Source/Xcode/LastSupper/Resources/event/TestScript.txt";
    string script = "TestScript.txt";
    string path = fu->fullPathForFilename(script);
    const char* cstr = path.c_str();
    fp = fopen(cstr, "rb");
    Document doc;
    FileReadStream rs(fp, buf, sizeof(buf));
    doc.ParseStream(rs);
    fclose(fp);
    bool error = doc.HasParseError();
    if(error){
        size_t offset = doc.GetErrorOffset();
        ParseErrorCode code = doc.GetParseError();
        const char* msg = GetParseError_En(code);
        printf("%d:%d(%s)\n", static_cast<int>(offset), code, msg);
    }
    const rapidjson::Value& id = doc["1"];
    const char* v = id["type"].GetString();
    printf("type = %s\n", v);
    return;
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