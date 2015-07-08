//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScriptManager.h"
#include "TitleScene.h"

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
        {"repeat", &EventScriptManager::repeat},    //繰り返し実行
        {"flagif", &EventScriptManager::flagif},        //flagによって場合分けして実行
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
//
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
        FunctionPointer func;
        func = EventScriptManager::event_map.at(type);
        if(!func){
            //default :
        } else {
            Ref* targetAct = (this->*func)(event);
            if(targetAct != nullptr){
                this->layer->runAction(dynamic_cast<FiniteTimeAction*>(targetAct));
            }
        }
    }
    return true;
}

//event配列actionのVectorを返す配列
cocos2d::Vector<FiniteTimeAction*> EventScriptManager::createActionVec(rapidjson::Value& subAction)
{
    FUNCLOG
    SizeType len = subAction.Size();
    cout << "   len=" << len << endl;
    string type;
    Vector<FiniteTimeAction*> acts;
    for(int i=0;i<len;i++){
        type = static_cast<string>(subAction[i]["type"].GetString());
        cout << "   type=" << type << endl;
        FunctionPointer func;
        func = this->event_map.at(type);
        if(!func){
            //default :
        } else {
            Ref* targetAct = (this->*func)(subAction[i]);
            if(targetAct != nullptr){
                acts.pushBack(dynamic_cast<FiniteTimeAction*>(targetAct));
            }
        }
    }
    //acts.pushBack(nullptr);
    return acts;
}

// --------------------------------
//       Instruct functions
// --------------------------------

/**
 * run sequence
 * @param type: string >> sequence
 * @param action: array json >> array of instructs
 */
Ref* EventScriptManager::sequence(rapidjson::Value& event)
{
    FUNCLOG
    return static_cast<Ref*>(Sequence::create(this->createActionVec(event["action"])));
}

/**
 * run spawn
 * @param type: string >> spawn
 * @param action: array json >> array of instructs
 */
Ref* EventScriptManager::spawn(rapidjson::Value& event)
{
    FUNCLOG
    return static_cast<Ref*>(Spawn::create(this->createActionVec(event["action"])));
}

/**
 * run repeat
 * @param type: string >> repeat
 * @param loop: int >> loop count
 * @param action: array json >> array of instruts
 */
Ref* EventScriptManager::repeat(rapidjson::Value &event)
{
    FUNCLOG
    Vector<FiniteTimeAction*> repeatAct;
    Vector<FiniteTimeAction*> origin = this->createActionVec(event["action"]);
    int loop = event["loop"].GetInt();
    for(int i=0;i<loop; i++){
        repeatAct.pushBack(origin);
    }
    return static_cast<Ref*>(Sequence::create(repeatAct));
}

/**
 * flagif
 * @param type: string >> flagif
 * @param map: int >> map_id
 * @param flag: int >> flag_id
 * @param true: array json >> array of instructs
 * @param false: array json >> array of instructs
 */
Ref* EventScriptManager::flagif(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

// --------------------------------
//       Event functions
// --------------------------------
/**
 * change map
 * @param type: string >> changeMap
 * @param ?
 */
Ref* EventScriptManager::changeMap(rapidjson::Value& event)
{
    FUNCLOG
    //とりあえずテストでタイトル画面に移動するように設計してある
	return static_cast<Ref*>(CallFunc::create([=](){Director::getInstance()->replaceScene(TitleScene::createScene());}));
}
/** 
 * Move object
 * @param type: string >> move
 * @param object: string >> name of object
 * @param time: string >> time of move
 * @param x: int >> move x points
 * @param y: int >> move y points
 */
Ref* EventScriptManager::move(rapidjson::Value& event)
{
    FUNCLOG
    double scale = 16.0;
    float x = static_cast<float>(event["x"].GetDouble() * scale);
    float y = static_cast<float>(event["y"].GetDouble() * scale);
    return static_cast<Ref*>(TargetedAction::create(this->layer->getChildByName(this->json["name"].GetString())->getChildByName(event["object"].GetString()), MoveBy::create(static_cast<float>(event["time"].GetDouble()), Point(x, y))));
}

/**
 * play sounud effect
 * @param type: string >> playSE
 * @param file: string >> filename
 */
Ref* EventScriptManager::playSE(rapidjson::Value& event)
{
    FUNCLOG
    string file = event["file"].GetString();
    cout << "playSE >> " << file << endl;
    return static_cast<Ref*>(CallFunc::create([=](){}));
}

/**
 * play back ground music
 * @param type: string >> playBGM
 * @param file: string >> filename
 */
Ref* EventScriptManager::playBGM(rapidjson::Value &event)
{
    FUNCLOG
    string file = event["file"].GetString();
    cout << "playBGM >> " << file << endl;
    return static_cast<Ref*>(CallFunc::create([=](){}));

}

Ref* EventScriptManager::message(rapidjson::Value& event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptManager::talk(rapidjson::Value& event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptManager::fade(rapidjson::Value& event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptManager::control(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptManager::read(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}