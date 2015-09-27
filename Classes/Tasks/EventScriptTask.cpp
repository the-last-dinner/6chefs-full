//
//  EventScriptTask.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/05.
//
//

#include "Tasks/EventScriptTask.h"

#include "Scenes/DungeonScene.h"
#include "Scenes/TitleScene.h"
#include "MapObjects/Objects.h"
#include "Layers/Message/CharacterMessageLayer.h"
#include "Layers/Message/SystemMessageLayer.h"

#include "Layers/Dungeon/TiledMapLayer.h"

//イベント関数の関数ポインタ格納
const map<string, EventScriptTask::FunctionPointer> EventScriptTask::EVENT_MAP =
{
    //命令タイプ
    {"sequence", &EventScriptTask::sequence},    //順番に処理を実行
    {"spawn", &EventScriptTask::spawn},       //同時に処理を実行
    {"repeat", &EventScriptTask::repeat},    //繰り返し実行
    {"if", &EventScriptTask::ifelse},    //flagによって場合分けして実行
    //イベントタイプ
    {"changeMap", &EventScriptTask::changeMap},//マップ移動
    {"move", &EventScriptTask::move},     //オブジェクトの移動
    {"storyMsg", &EventScriptTask::storyMsg},   //ストーリーメッセージ
    {"charaMsg", &EventScriptTask::charaMsg},       //キャラメッセージ
    {"questionMsg", &EventScriptTask::questionMsg},     //はいいいえ選択肢
    {"systemMsg", &EventScriptTask::systemMsg},    //システムのメッセージ
    {"talk", &EventScriptTask::talk},     //キャラクターの会話
    {"fade", &EventScriptTask::fade},     //画面特殊効果
    {"playSE", &EventScriptTask::playSE},   //効果音再生
    {"playBGM", &EventScriptTask::playBGM}, //BGM再生
    {"control", &EventScriptTask::control}, //操作状態の変更
    {"read", &EventScriptTask::read},      //書物読んでるモード
    {"changeFlg", &EventScriptTask::changeFlg}
};
const map<string, EventScriptTask::FunctionPointerC> EventScriptTask::CONDITION_MAP =
{
    //if分の種類
    {"event", &EventScriptTask::eventIf},
    {"item", &EventScriptTask::itemIf},
    {"flag", &EventScriptTask::flagIf},
    {"equip", &EventScriptTask::equipIf},
    {"status", &EventScriptTask::statusIf}
};

// コンストラクタ
EventScriptTask::EventScriptTask(){FUNCLOG}

// デストラクタ
EventScriptTask::~EventScriptTask(){FUNCLOG}

// 初期化
bool EventScriptTask::init(DungeonScene* scene)
{
	FUNCLOG
	if(!scene) return false;
	this->scene = scene;
	return true;
}

// イベントスクリプトを実行
void EventScriptTask::runEventScript(int eventId)
{
    FUNCLOG
	CCLOG("EVENT ID >> %d", eventId);
	rapidjson::Value& action { EventScriptManager::getInstance()->getScript(eventId) };
    //イベントステータスの初期化
    this->event_status = 0;
	//各命令の処理
    if(!action.IsNull()) this->dealScript(action);
}

//各イベント命令処理の場合分け
void EventScriptTask::dealScript(rapidjson::Value &action)
{
    FUNCLOG
    SizeType len = action.Size();
    cout << "   len=" << len << endl;
    string type;
    for(int i=0;i<len;i++){
        rapidjson::Value& event = action[i];
        type = static_cast<string>(event["type"].GetString());
        cout << "   type=" << type << endl;
        EventScriptTask::FunctionPointer func;
        func = EventScriptTask::EVENT_MAP.at(type);
        if(!func){
            //default :
        } else {
            Ref* target_act = (this->*func)(event);
            if(target_act != nullptr){
                this->scene->runAction(dynamic_cast<FiniteTimeAction*>(target_act));
            }
        }
    }
    return;
}

//event配列actionのVectorを返す配列
cocos2d::Vector<FiniteTimeAction*> EventScriptTask::createActionVec(rapidjson::Value &sub_act)
{
    FUNCLOG
    SizeType len = sub_act.Size();
    cout << "   len=" << len << endl;
    string type;
    Vector<FiniteTimeAction*> acts;
    for(int i=0;i<len;i++){
        type = static_cast<string>(sub_act[i]["type"].GetString());
        cout << "   type=" << type << endl;
        EventScriptTask::FunctionPointer func;
        func = EventScriptTask::EVENT_MAP.at(type);
        if(!func){
            //default :
        } else {
            Ref* target_act = (this->*func)(sub_act[i]);
            if(target_act != nullptr){
                acts.pushBack(dynamic_cast<FiniteTimeAction*>(target_act));
            }
        }
    }
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
Ref* EventScriptTask::sequence(rapidjson::Value& event)
{
    FUNCLOG
    return static_cast<Ref*>(Sequence::create(this->createActionVec(event["action"])));
}

/**
 * run spawn
 * @param type: string >> spawn
 * @param action: array json >> array of instructs
 */
Ref* EventScriptTask::spawn(rapidjson::Value& event)
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
Ref* EventScriptTask::repeat(rapidjson::Value &event)
{
    FUNCLOG
    Vector<FiniteTimeAction*> repeat_act;
    Vector<FiniteTimeAction*> origin = this->createActionVec(event["action"]);
    int loop = event["loop"].GetInt();
    for(int i=0;i<loop; i++){
        repeat_act.pushBack(origin);
    }
    return static_cast<Ref*>(Sequence::create(repeat_act));
}

/**
 * ifelse
 * @param type: string >> ifelse
 * @param map: int >> map_id
 * @param flag: int >> flag_id
 * @param true: array json >> array of instructs
 * @param false: array json >> array of instructs
 */
Ref* EventScriptTask::ifelse(rapidjson::Value &event)
{
    FUNCLOG
    if(this->judgeCondition(event["condition"]))
    {
        if(event.HasMember("action"))
        {
            return static_cast<Ref*>(Spawn::create(this->createActionVec(event["action"])));
        }
        if(event.HasMember("eventID"))
        {
            int eventId {0};
            if(event["eventID"].IsInt())
            {
                eventId = event["eventID"].GetInt();
            } else
            {
                eventId = stoi(event["eventID"].GetString());
            }
            return static_cast<Ref*>(CallFunc::create([=](){this->runEventScript(eventId);}));
        }
    }
    return nullptr;
}

// if分のconditionのboolを判定
bool EventScriptTask::judgeCondition(rapidjson::Value& cond)
{
    FUNCLOG
    EventScriptTask::FunctionPointerC func_c;
    SizeType len = cond.Size();
    bool judge {false};
    bool reverse {false};
    for(int i=0; i<len; i++)
    {
        for(rapidjson::Value::MemberIterator itr = cond[i].MemberBegin(); itr != cond[i].MemberEnd(); itr++)
        {
            string key {itr->name.GetString()};
            if(key.find("N") == 0)
            {
                key = this->strReplace("N", "", key);
                reverse = true;
            }
            func_c = EventScriptTask::CONDITION_MAP.at(key);
            // N判定
            judge = (this->*func_c)(itr->value, reverse);
            //ANDなのでfalseがあったらbreak;
            if(!judge) break;
        }
        //ORなのでtrueがあったらbreak;してreturn;
        if(judge) break;
    }
    return judge;
}

//イベントフラグチェック
bool EventScriptTask::eventIf(rapidjson::Value& cond, bool reverse)
{
    FUNCLOG
    bool judge;
    if(cond[0].IsArray())
    {
        //複数のイベント
        SizeType size = cond.Size();
        for(int i=0; i<size; i++)
        {
            judge = PlayerDataManager::getInstance()->getEventFlag(stoi(cond[i][0].GetString()), stoi(cond[i][1].GetString()));
            if(reverse) judge = !judge;
            if(!judge) return false;
        }
    } else {
        //一つのイベント
        judge = PlayerDataManager::getInstance()->getEventFlag(stoi(cond[0].GetString()), stoi(cond[1].GetString()));
        if(reverse) judge = !judge;
    }
    return judge;
}

// アイテム所持チェック
bool EventScriptTask::itemIf(rapidjson::Value& cond, bool reverse)
{
    FUNCLOG
    SizeType size = cond.Size();
    bool judge;
    for(int i=0; i<size; i++)
    {
        judge = PlayerDataManager::getInstance()->checkItem(stoi(cond[i].GetString()));
        if(reverse) judge = !judge;
        if(!judge) break;
    }
    return judge;
}

//　イベント固有フラグチェック
bool EventScriptTask::flagIf(rapidjson::Value& cond, bool reverse)
{
    FUNCLOG
    bool judge {this->event_status == stoi(cond.GetString())};
    if(reverse) judge = !judge;
    return judge;
}

//アイテム装備チェック
bool EventScriptTask::equipIf(rapidjson::Value& cond, bool reverse)
{
    FUNCLOG
    bool judge;
    SizeType size = cond.Size();
    for(int i=0; i<size; i++)
    {
        judge = PlayerDataManager::getInstance()->checkItemEquipment(stoi(cond[i].GetString()));
        if(reverse) judge = !judge;
        if(!judge) break;
    }
    return judge;
}

//キャラクターの好感度チェック
bool EventScriptTask::statusIf(rapidjson::Value& cond, bool reverse)
{
    FUNCLOG
    bool judge;
    if(cond[0].IsArray())
    {
        //複数の好感度
        SizeType size = cond.Size();
        for(int i=0; i<size; i++)
        {
            judge = PlayerDataManager::getInstance()->checkFriendship(cond[i][0].GetString(), stoi(cond[i][1].GetString()));
            if(reverse) judge = !judge;
            if(!judge) break;
        }
    } else {
        //一つのイベント
        judge = PlayerDataManager::getInstance()->checkFriendship(cond[0].GetString(), stoi(cond[1].GetString()));
        if(reverse) judge = !judge;
    }
    return judge;
}

// --------------------------------
//       Event functions
// --------------------------------
/**
 * change map
 * @param type: string >> changeMap
 * @param map_id: string
 * @param x: int
 * @param y: int
 * @param direction: int (default: null)
 */
Ref* EventScriptTask::changeMap(rapidjson::Value& event)
{
    FUNCLOG
    if (event.HasMember("direction"))
    {
        //directionが指定されている場合
        PlayerDataManager::getInstance()->setLocation(PlayerDataManager::Location(stoi(event["mapID"].GetString()), event["x"].GetInt(), event["y"].GetInt(), event["direction"].GetInt()));
    }  else
    {
        //directionが指定されていない場合は移動直前の方向を取得
        Character* hero {this->scene->mapLayer->getHeroObject()};
        PlayerDataManager::getInstance()->setLocation(PlayerDataManager::Location(stoi(event["mapID"].GetString()), event["x"].GetInt(), event["y"].GetInt(), hero->getDirection()));
    }
    return static_cast<Ref*>(CallFunc::create([=](){Director::getInstance()->replaceScene(DungeonScene::createScene());}));
}

/**
 * Move object
 * @param type: string >> move
 * @param object: string >> name of object
 * @param time: string >> time of move
 * @param x: int >> move x points
 * @param y: int >> move y points
 */
Ref* EventScriptTask::move(rapidjson::Value& event)
{
    FUNCLOG
    double scale = 16.0;
    float x = static_cast<float>(event["x"].GetDouble() * scale);
    float y = static_cast<float>(event["y"].GetDouble() * scale);
    return static_cast<Ref*>(TargetedAction::create(this->scene->mapLayer->getChildByName(EventScriptManager::getInstance()->getMapId())->getChildByName(event["object"].GetString()), MoveBy::create(static_cast<float>(event["time"].GetDouble()), Point(x, y))));
}

/**
 * play sounud effect
 * @param type: string >> playSE
 * @param file: string >> filename
 */
Ref* EventScriptTask::playSE(rapidjson::Value& event)
{
    FUNCLOG
    string file = event["file"].GetString();
    cout << "playSE >> " << file << endl;
    return static_cast<Ref*>(CallFunc::create([=](){SoundManager::getInstance()->playSound("se/" + file);}));
}

/**
 * play back ground music
 * @param type: string >> playBGM
 * @param file: string >> filename
 */
Ref* EventScriptTask::playBGM(rapidjson::Value &event)
{
    FUNCLOG
    string file = event["file"].GetString();
    cout << "playBGM >> " << file << endl;
    return static_cast<Ref*>(CallFunc::create([=](){SoundManager::getInstance()->playSound("bgm/" + file);}));
    
}

Ref* EventScriptTask::storyMsg(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptTask::charaMsg(rapidjson::Value& event)
{
    FUNCLOG
    queue<CharacterMessageLayer::Information> infos {};
    if(event.HasMember("talk"))
    {
        //複数人での会話時
        SizeType len {event["talk"].Size()}; //会話人数の取得
        for(SizeType i {0}; i<len; i++)
        {
            rapidjson::Value& chara = event["talk"][i];
            CharacterMessageLayer::Information info;
            info.charaId = stoi(chara["charaID"].GetString());
            info.charaName = (chara.HasMember("name")) ? chara["name"].GetString() : CsvDataManager::getInstance()->getDisplayName(CsvDataManager::DataType::CHARACTER, info.charaId);
            if(chara.HasMember("imgID")) info.imgId = stoi(chara["imgID"].GetString());
            //ページ数を取得してページごとにプッシュ
            SizeType text_len {chara["text"].Size()};
            for(SizeType j {0}; j<text_len; j++)
            {
                info.pages.push(chara["text"][j].GetString());
            }
            infos.push(info);
        }
    } else
    {
        //一人で話すとき
        CharacterMessageLayer::Information info;
        info.charaId = stoi(event["charaID"].GetString());
        if(event.HasMember("imgID")) info.imgId = stoi(event["imgID"].GetString());
        info.charaName = (event.HasMember("name")) ? event["name"].GetString() : CsvDataManager::getInstance()->getDisplayName(CsvDataManager::DataType::CHARACTER, info.charaId);
        //ページ数を取得してページごとにプッシュ
        SizeType text_len {event["text"].Size()};
        for(SizeType j {0}; j<text_len; j++)
        {
            info.pages.push(event["text"][j].GetString());
        }
        infos.push(info);
    }
    //メッセージウインドウをスタートする関数をリターン
    return static_cast<Ref*>(CallFunc::create([=]()
    {
        CharacterMessageLayer* message {CharacterMessageLayer::create(infos)};
        
        this->scene->addChild(message);
        message->start();
    }));
}

Ref* EventScriptTask::questionMsg(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptTask::systemMsg(rapidjson::Value &event)
{
    FUNCLOG
    queue<string> pages;
    SizeType len {event["text"].Size()};
    for (SizeType i {0}; i<len; i++) {
        pages.push(event["text"][i].GetString());
    }
    return static_cast<Ref*>(CallFunc::create([=]()
    {
        SystemMessageLayer* message {SystemMessageLayer::create(pages)};
        this->scene->addChild(message);
        message->start();
    }));
}

Ref* EventScriptTask::talk(rapidjson::Value& event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptTask::fade(rapidjson::Value& event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptTask::control(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

Ref* EventScriptTask::read(rapidjson::Value &event)
{
    FUNCLOG
    return nullptr;
}

// change flag
Ref* EventScriptTask::changeFlg(rapidjson::Value &event)
{
    FUNCLOG
    this->event_status = stoi(event["flg"].GetString());
    return nullptr;
}

// 文字列を置換する
string EventScriptTask::strReplace(const string& pattern, const string& replacement, string target)
{
    std::string::size_type Pos(target.find(pattern));
    while( Pos != std::string::npos )
    {
        target.replace( Pos, pattern.length(), replacement);
        Pos = target.find( pattern, Pos + replacement.length() );
    }
    return target;
}