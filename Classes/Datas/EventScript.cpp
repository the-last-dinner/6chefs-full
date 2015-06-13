//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScript.h"

using namespace std;
using namespace cocos2d;

// コンストラクタ
EventScript::EventScript():fu(FileUtils::getInstance())
{
    FUNCLOG
}

// デストラクタ
EventScript::~EventScript()
{
    FUNCLOG
}

//イベントスクリプトファイルの読み込み
void EventScript::readScript ()
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
    cout << json << endl;
    //jsonテキストを変換
    jsonToMap(json);
    return;
}

//与えられたjsonテキストを
using namespace rapidjson;
void EventScript::jsonToMap(string json){
    FUNCLOG
    FILE* fp;
    char buf[512];
    fp = fopen("/Users/Ryoya/Source/Xcode/LastSupper/Resources/event/TestScript.txt", "rb");
    Document doc;
    FileReadStream rs(fp, buf, sizeof(buf));
    doc.ParseStream(rs);
    fclose(fp);
    return;
}

//文字列のトリミング
string EventScript::trim(const string& string, const char* trimCharacterList = " \t\v\r\n")
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