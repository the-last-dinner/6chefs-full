//
//  ModalLayerEvent.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#include "Event/ModalLayerEvent.h"

#include "Event/EventScriptValidator.h"
#include "Event/EventScriptMember.h"

#include "Scenes/DungeonScene.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

#include "Datas/Message/CharacterMessageData.h"
#include "Datas/Message/StoryMessageData.h"
#include "Datas/Message/SystemMessageData.h"

#include "Layers/Message/CharacterMessagelayer.h"
#include "Layers/Message/StoryMessagelayer.h"
#include "Layers/Message/SystemMessagelayer.h"

#pragma mark ModalLayerEvent

// 初期化
bool ModalLayerEvent::init()
{
    if(!GameEvent::init()) return false;
    
    return true;
}

// モーダルレイヤを表示する時
void ModalLayerEvent::onOpenModalLayer()
{
    this->validator->getScene()->getListener()->setEnabled(false);
}

// モーダルレイヤを閉じる時
void ModalLayerEvent::onCloseModalLayer()
{
    this->setDone();
    this->validator->getScene()->getListener()->setEnabled(true);
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
        data->setCharaId(stoi(json[member::CHARA_ID].GetString()));
        
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
    this->onOpenModalLayer();
    this->validator->getScene()->addChild(CharacterMessageLayer::create(this->datas, CC_CALLBACK_0(ModalLayerEvent::onCloseModalLayer, this)));
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
    this->onOpenModalLayer();
    this->validator->getScene()->addChild(StoryMessageLayer::create(this->title, this->datas, CC_CALLBACK_0(ModalLayerEvent::onCloseModalLayer, this)));
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
    FUNCLOG
    this->onOpenModalLayer();
    this->validator->getScene()->addChild(SystemMessageLayer::create(this->datas, CC_CALLBACK_0(ModalLayerEvent::onCloseModalLayer, this)));
}