//
//  EventScript.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/03/15.
//
//

#include "Event/EventScript.h"

// コンストラクタ
EventScript::EventScript() {FUNCLOG}

// デストラクタ
EventScript::~EventScript() {FUNCLOG}

// 初期化
bool EventScript::init(const string& jsonFileName)
{
    this->fu = FileUtils::getInstance();
    
    FILE* fp;
    char buf[512];
    //ファイルパス
    string path = this->fu->fullPathForFilename("event/" + jsonFileName + ".json");
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
vector<string> EventScript::getPreLoadList(string type){
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
rapidjson::Value& EventScript::getScriptJson(int eventId)
{
    rapidjson::Value::MemberIterator itr {this->json.FindMember(to_string(eventId).c_str())};
    if(itr == this->json.MemberEnd())
    {
        static rapidjson::Value nullValue;
        return nullValue;
    }
    return itr->value;
}