//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "Managers/EventScriptManager.h"

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
EventScriptManager::EventScriptManager():fu(FileUtils::getInstance()){FUNCLOG}

// デストラクタ
EventScriptManager::~EventScriptManager(){FUNCLOG}

//イベントスクリプトファイルの読み込み
bool EventScriptManager::setEventScript(string script)
{
    FUNCLOG
    FILE* fp;
    char buf[512];
    //ファイルパス
    string path = this->fu->fullPathForFilename("event/" +script + ".json");
    const char* cstr = path.c_str();
    //JSONファイルを読み込んでインスタンス変数jsonに格納
    fp = fopen(cstr, "rb");
    FileReadStream rs(fp, buf, sizeof(buf));
    this->json.ParseStream(rs);
    fclose(fp);
    //JSONの文法エラーチェック
    if(this->json.HasParseError()){
        //エラーがあった場合
        size_t offset = this->json.GetErrorOffset();
        ParseErrorCode code = this->json.GetParseError();
        const char* msg = GetParseError_En(code);
        printf("JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
        return false;
    } else {
        //エラーがなかった場合
        //this->map_id = this->json["map_id"].GetString();
#ifdef DEBUG
        //テスト出力
        ifstream filein(path);
        for (string line; getline(filein, line);)
        {
            cout << line << endl;
        }
#endif
        return true;
    }
}

//リソースのプリロード関数
vector<string> EventScriptManager::getPreLoadList(string type){
    vector<string> list {};
    const char* typec = type.c_str();
    if (!this->json.HasMember(typec)) return list;
    rapidjson::Value& obj = this->json[typec];
    SizeType len = obj.Size();
    for(int i=0;i<len;i++){
        list.push_back(obj[i].GetString());
    }
    return list;
}

// 該当idのスクリプトを取得
rapidjson::Value& EventScriptManager::getScript(int eventId)
{
	rapidjson::Value::MemberIterator itr {this->json.FindMember(to_string(eventId).c_str())};
	if(itr == this->json.MemberEnd())
	{
		static rapidjson::Value nullValue;
		return nullValue;
	}
	return itr->value;
}

// 現在のmap_idの取得
string EventScriptManager::getMapId()
{
    return this->map_id;
}