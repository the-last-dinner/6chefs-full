//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScriptManager.h"
#include "LoadScene.h"

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
{
    FUNCLOG
    //イベント関数の関数ポインタ格納
    event_map = {
        //命令タイプ
        {"sequence", &EventScriptManager::sequence},    //順番に処理を実行
        {"spawn", &EventScriptManager::spawn},       //同時に処理を実行
        {"flag", &EventScriptManager::flag},        //flagによって場合分けして実行
        //イベントタイプ
        {"changeMap", &EventScriptManager::changeMap},//マップ移動
        {"move", &EventScriptManager::move},     //オブジェクトの移動
        {"message", &EventScriptManager::message},  //システムのメッセージ
        {"talk", &EventScriptManager::talk},     //キャラクターの会話
        {"fade", &EventScriptManager::fade},     //画面特殊効果
        {"playSE", &EventScriptManager::playSE},   //効果音再生
        {"playBGM", &EventScriptManager::playBGM},  //BGM再生
        {"control", &EventScriptManager::control},  //操作状態の変更
        {"read", &EventScriptManager::read}      //書物読んでるモード
    };
}

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
    string path = this->fu->fullPathForFilename("event/" +script + ".json");
    const char* cstr = path.c_str();
    //JSONファイルを読み込んでインスタンス変数jsonに格納
    fp = fopen(cstr, "rb");
    FileReadStream rs(fp, buf, sizeof(buf));
    this->json.ParseStream(rs);
    fclose(fp);
    //JSONの文法エラーチェック
    bool error = this->json.HasParseError();
    if(error){
        //エラーがあった場合
        size_t offset = this->json.GetErrorOffset();
        ParseErrorCode code = this->json.GetParseError();
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
        return true;
    }
}

//リソースのプリロード関数
vector<string> EventScriptManager::getPreLoadList(string type){
    vector<string> list;
    const char* typec = type.c_str();
    rapidjson::Value& obj = this->json[typec];
    SizeType len = obj.Size();
    for(int i=0;i<len;i++){
        list.push_back(obj[i].GetString());
    }
    return list;
}

//マップ初期化処理
bool EventScriptManager::setDungeonScene(Layer* mainLayer)
{
    FUNCLOG
    //レイヤーをインスタンス変数に登録
    this->layer = mainLayer;
    //イベントスクリプト初期化イベントのeventID0番を実行
    bool success = this->runEvent(0);
    return success;
}

//イベントIDからイベントを実行
bool EventScriptManager::runEvent(int id)
{
    //idをint型からchar*に変換
    string sid = to_string(id);
    const char* csid = sid.c_str();
    //JsonEventScriptのidから命令
    cout << "eventID>>" << csid << endl;
    rapidjson::Value& action = this->json[csid];//jsonオブジェクト配列
    //各命令の処理
    this->dealScript(action);
    return true;
}

//各イベント命令処理の場合分け
bool EventScriptManager::dealScript(rapidjson::Value& action)
{
    SizeType len = action.Size();
    cout << "   len=" << len << endl;
    string type;
    for(int i=0;i<len;i++){
        rapidjson::Value& event = action[i];
        type = static_cast<string>(event["type"].GetString());
        cout << "   type=" << type << endl;
        if(type == "sequence" || type == "spawn"){
            rapidjson::Value& subAction = event["action"];
            this->dealScript(subAction);
        } else if (type == "move" || type == "changeMap") {
            FunctionPointer func;
            func = EventScriptManager::event_map.at(type);
            if(!func){
                //default :
            } else {
                this->layer->runAction(dynamic_cast<FiniteTimeAction*>((this->*func)(event)));
            }
        }
    }
    return true;
}

/**
 * 命令関数群
 */
Ref* EventScriptManager::sequence(rapidjson::Value& event)
{
    FUNCLOG
    
}

Ref* EventScriptManager::spawn(rapidjson::Value& event)
{
    FUNCLOG
}

Ref* EventScriptManager::flag(rapidjson::Value &event)
{
    FUNCLOG
}

/**
 * イベント関数群
 */
Ref* EventScriptManager::changeMap(rapidjson::Value& event)
{
    FUNCLOG
    //とりあえずテストでタイトル画面に移動するように設計してある
    return static_cast<Ref*>(CallFunc::create([=](){Director::getInstance()->replaceScene(LoadScene::createScene(SceneType::TITLE));}));
}

Ref* EventScriptManager::move(rapidjson::Value& event)
{
    FUNCLOG
    cout << "This is move!" << endl;
    return static_cast<Ref*>(TargetedAction::create(this->layer->getChildByName("map")->getChildByName("magoichi"), MoveBy::create(1.0f, Point(32.f, 32.f))));
}

Ref* EventScriptManager::message(rapidjson::Value& event)
{
    FUNCLOG
}

Ref* EventScriptManager::talk(rapidjson::Value& event)
{
    FUNCLOG
}

Ref* EventScriptManager::fade(rapidjson::Value& event)
{
    FUNCLOG
}

Ref* EventScriptManager::playSE(rapidjson::Value& event)
{
    FUNCLOG
}

Ref* EventScriptManager::playBGM(rapidjson::Value &event)
{
    FUNCLOG
}

Ref* EventScriptManager::control(rapidjson::Value &event)
{
    FUNCLOG
}

Ref* EventScriptManager::read(rapidjson::Value &event)
{
    FUNCLOG
}