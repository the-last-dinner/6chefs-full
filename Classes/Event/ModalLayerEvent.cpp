//
//  ModalLayerEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#include "Event/ModalLayerEvent.h"

#include "Event/EventFactory.h"
#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "Scenes/DungeonScene.h"

#include "Datas/Message/CharacterMessageData.h"
#include "Datas/Message/StoryMessageData.h"
#include "Datas/Message/SystemMessageData.h"

#include "Layers/Dungeon/ButtonMashingLayer.h"
#include "Layers/Dungeon/DisplayImageLayer.h"
#include "Layers/Dungeon/SelectEventLayer.h"
#include "Layers/Message/CharacterMessagelayer.h"
#include "Layers/Message/StoryMessagelayer.h"
#include "Layers/Message/SystemMessagelayer.h"

#include "Managers/DungeonSceneManager.h"

#pragma mark ModalLayerEvent

// 初期化
bool ModalLayerEvent::init()
{
    if(!GameEvent::init()) return false;
    
    return true;
}

#pragma mark -
#pragma mark CharacterMessage

bool CharacterMessage::init(rapidjson::Value& json)
{
    if(!ModalLayerEvent::init()) return false;
    
    queue<CharacterMessageData*> datas {};
    
    //複数人での会話時
    if(this->validator->hasMember(json, member::TALK))
    {
        //会話人数の取得
        SizeType len {json[member::TALK].Size()};
        
        for(SizeType i { 0 }; i < len; i++)
        {
            rapidjson::Value& chara { json[member::TALK][i] };
            
            //ページ数を取得してページごとにプッシュ
            SizeType text_len {chara[member::TEXT].Size()};
            
            queue<string> pages {};
            
            for(SizeType j { 0 }; j < text_len; j++)
            {
                pages.push(chara[member::TEXT][j].GetString());
            }
            
            CharacterMessageData* data {CharacterMessageData::create(pages)};
            CC_SAFE_RETAIN(data);
            
            // キャラID
            data->setCharaId(stoi(chara[member::CHARA_ID].GetString()));
            
            // キャラ名
            string charaName {};
            
            if(this->validator->hasMember(chara, member::NAME))
            {
                charaName = chara[member::NAME].GetString();
            }
            else
            {
                charaName = CsvDataManager::getInstance()->getCharaName(data->getCharaId());
            }
            
            data->setCharaName(charaName);
            
            // 画像ID
            if(this->validator->hasMember(chara, member::IMG_ID)) data->setImgId(stoi(chara[member::IMG_ID].GetString()));
            
            datas.push(data);
        }
    }
    //一人で話すとき
    else
    {
        //ページ数を取得してページごとにプッシュ
        SizeType text_len {json[member::TEXT].Size()};
        queue<string> pages {};
        
        for(SizeType j {0}; j < text_len; j++)
        {
            pages.push(json[member::TEXT][j].GetString());
        }
        
        CharacterMessageData* data {CharacterMessageData::create(pages)};
        CC_SAFE_RETAIN(data);
        
        // キャラID
        if(this->validator->hasMember(json, member::CHARA_ID)) data->setCharaId(stoi(json[member::CHARA_ID].GetString()));
        
        // キャラ名
        string charaName {};
        
        if(this->validator->hasMember(json, member::NAME))
        {
            charaName = json[member::NAME].GetString();
        }
        else
        {
            charaName = CsvDataManager::getInstance()->getCharaName(data->getCharaId());
        }
        
        // 画像ID
        if(this->validator->hasMember(json, member::IMG_ID)) data->setImgId(stoi(json[member::IMG_ID].GetString()));
        
        datas.push(data);
    }
    
    this->datas = datas;
    
    return true;
}

void CharacterMessage::run()
{
    DungeonSceneManager::getInstance()->getScene()->addChild(CharacterMessageLayer::create(this->datas, [this]{this->setDone();}), Priority::CHARACTER_MESSAGE);
}

#pragma mark -
#pragma mark StoryMessage

bool StoryMessage::init(rapidjson::Value& json)
{
    if(!ModalLayerEvent::init()) return false;
    
    // タイトル
    if(this->validator->hasMember(json, member::TITLE))
    {
        this->title = json[member::TITLE].GetString();
    }
    
    queue<StoryMessageData*> datas;
    SizeType len {json[member::TEXT].Size()};
    
    for (SizeType i {0}; i < len; i++)
    {
        StoryMessageData* data {StoryMessageData::create(json[member::TEXT][i].GetString())};
        CC_SAFE_RETAIN(data);
        datas.push(data);
    }
    
    this->datas = datas;
    
    return true;
}

void StoryMessage::run()
{
    DungeonSceneManager::getInstance()->getScene()->addChild(StoryMessageLayer::create(this->title, this->datas, [this]{this->setDone();}), Priority::STORY_MESSAGE);
}

#pragma mark -
#pragma mark SystemMessage

bool SystemMessage::init(rapidjson::Value& json)
{
    if(!ModalLayerEvent::init()) return false;
    
    queue<SystemMessageData*> datas;
    SizeType len {json[member::TEXT].Size()};
    
    for (SizeType i {0}; i < len; i++)
    {
        SystemMessageData* data {SystemMessageData::create(json[member::TEXT][i].GetString())};
        CC_SAFE_RETAIN(data);
        datas.push(data);
    }
    
    this->datas = datas;
    
    return true;
}

void SystemMessage::run()
{
    DungeonSceneManager::getInstance()->getScene()->addChild(SystemMessageLayer::create(this->datas, [this]{this->setDone();}), Priority::SYSTEM_MESSAGE);
}

#pragma mark -
#pragma mark DispImageEvent

bool DispImageEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // ファイル名
    if(!this->validator->hasMember(json, member::FILE)) return false;
    this->fileName = json[member::FILE].GetString();
    
    // 表示時間
    if(this->validator->hasMember(json, member::TIME)) this->duration = json[member::TIME].GetDouble();
    
    return true;
}

void DispImageEvent::run()
{
    DisplayImageLayer* layer { DisplayImageLayer::create(this->fileName, this->duration, [this]{this->setDone();}) };

    if(!layer)
    {
        this->setDone();
        
        return;
    }
    
    DungeonSceneManager::getInstance()->getScene()->addChild(layer, Priority::DISP_IMAGE_LAYER);
}

#pragma mark -
#pragma mark ButtonMashingEvent

bool ButtonMashingEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // 連打回数
    if(!this->validator->hasMember(json, member::TIMES)) return false;
    this->count = json[member::TIMES].GetInt();
    
    // 制限時間
    if(!this->validator->hasMember(json, member::LIMIT)) return false;
    this->limit = json[member::LIMIT].GetDouble();
    
    // 成功時イベント
    if(this->validator->hasMember(json, member::TRUE_))
    {
        if(json[member::TRUE_].IsString()) this->sEventId = stoi(json[member::TRUE_].GetString());
        if(json[member::TRUE_].IsArray()) this->sEvent = this->factory->createGameEvent(json[member::TRUE_]);
        CC_SAFE_RETAIN(this->sEvent);
    }
    
    // 失敗時イベント
    if(this->validator->hasMember(json, member::FALSE_))
    {
        if(json[member::FALSE_].IsString()) this->fEventId = stoi(json[member::FALSE_].GetString());
        if(json[member::FALSE_].IsArray()) this->fEvent = this->factory->createGameEvent(json[member::FALSE_]);
        CC_SAFE_RETAIN(this->fEvent);
    }
    
    return true;
}

void ButtonMashingEvent::run()
{
    ButtonMashingLayer* layer { ButtonMashingLayer::create(this->count, this->limit, [this](ButtonMashingLayer::Result result)
        {
            this->setDone();
            
            if(result == ButtonMashingLayer::Result::SUCCESS)
            {
                if(this->sEvent)
                {
                    this->event = this->sEvent;
                    this->sEvent = nullptr;
                }
                else
                {
                    // ID指定の場合
                    DungeonSceneManager::getInstance()->pushEventFront(this->sEventId);
                }
            }
            else
            {
                if(this->fEvent)
                {
                    this->event = this->fEvent;
                    this->fEvent = nullptr;
                }
                else
                {
                    // ID指定の場合
                    DungeonSceneManager::getInstance()->pushEventFront(this->fEventId);
                }
            }
            
            // イベント実行
            DungeonSceneManager::getInstance()->pushEventFront(this->event);
        }) };
    
    if(!layer)
    {
        this->setDone();
        
        return;
    }
    
    DungeonSceneManager::getInstance()->getScene()->addChild(layer, Priority::BUTTON_MASHING_LAYER);
}

#pragma mark -
#pragma mark SelectEvent

bool SelectEvent::init(rapidjson::Value& json)
{
    if(!GameEvent::init()) return false;
    
    // 質問文
    if(!this->validator->hasMember(json, member::TEXT)) return false;
    this->message = json[member::TEXT][0].GetString();
    
    // 選択肢
    if(!this->validator->hasMember(json, member::CHOICES) || !json[member::CHOICES].IsArray()) return false;
    rapidjson::Value& choicesJson { json[member::CHOICES] };
    for(int i { 0 }; i < choicesJson.Size(); i++)
    {
        rapidjson::Value& choiceJson {choicesJson[i]};
        
        // 選択肢の表示ラベル
        if(!this->validator->hasMember(choiceJson, member::CHOICE)) return false;
        this->choices.push_back(choiceJson[member::CHOICE].GetString());
        
        // 選択肢のコールバックイベント
        int eventId { static_cast<int>(EventID::UNDIFINED) };
        GameEvent* event { nullptr };
        if(this->validator->hasMember(choiceJson, member::ACTION)) event = this->factory->createGameEvent(choiceJson[member::ACTION]);
        if(this->validator->hasMember(choiceJson, member::EVENT_ID)) eventId = stoi(choiceJson[member::EVENT_ID].GetString());
        CC_SAFE_RETAIN(event);
        this->eventCallBacks.push_back(SelectCallBack({eventId, event}));
    }
    
    return true;
}

void SelectEvent::run()
{
    SelectEventLayer* layer { SelectEventLayer::create(this->message, this->choices) };
    
    // コールバック
    layer->onSelected = [this](const int idx)
    {
        // 選ばれた選択肢のインデックスからコールバックを決定
        SelectCallBack callback {this->eventCallBacks.at(idx)};
        
        // コールバック実行
        DungeonSceneManager::getInstance()->pushEventFront(callback.first);
        DungeonSceneManager::getInstance()->pushEventFront(callback.second);
        
        this->setDone();
    };
    
    DungeonSceneManager::getInstance()->getScene()->addChild(layer, Priority::SELECT_LAYER);
}
