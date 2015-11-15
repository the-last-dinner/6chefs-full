//
//  ModalLayerEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#ifndef __LastSupper__MessageEvent__
#define __LastSupper__MessageEvent__

#include "Event/GameEvent.h"

class CharacterMessageData;
class StoryMessageData;
class SystemMessageData;

class ModalLayerEvent : public GameEvent
{
// インスタンスメソッド
protected:
    ModalLayerEvent() {};
    ~ModalLayerEvent() {};
    virtual bool init() override;
};

// キャラクターメッセージイベント
class CharacterMessage : public ModalLayerEvent
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CharacterMessage, rapidjson::Value&)

// インスタンス変数
private:
    queue<CharacterMessageData*> datas {};

// インスタンスメソッド
private:
    CharacterMessage() {FUNCLOG};
    ~CharacterMessage() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    void run() override;
};

// ストーリメッセージイベント
class StoryMessage : public ModalLayerEvent
{
public:
    CREATE_FUNC_WITH_PARAM(StoryMessage, rapidjson::Value&)
    
private:
    string title {};
    queue<StoryMessageData*> datas {};
    
private:
    StoryMessage():title("") {FUNCLOG};
    ~StoryMessage() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// システムメッセージイベント
class SystemMessage : public ModalLayerEvent
{
public:
    CREATE_FUNC_WITH_PARAM(SystemMessage, rapidjson::Value&)

private:
    queue<SystemMessageData*> datas {};
    
private:
    SystemMessage() {FUNCLOG};
    ~SystemMessage() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// 画像を表示
class DispImageEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(DispImageEvent, rapidjson::Value&)
private:
    string fileName {};
    float duration { 0.f };
private:
    DispImageEvent() {FUNCLOG};
    ~DispImageEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// 連打イベント
class ButtonMashingEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(ButtonMashingEvent, rapidjson::Value&)
private:
    int count { 0 };
    float limit { 0.f };
    int sEventId { static_cast<int>(EventID::UNDIFINED) };
    int fEventId { static_cast<int>(EventID::UNDIFINED) };
    GameEvent* sEvent { nullptr };
    GameEvent* fEvent { nullptr };
    GameEvent* event { nullptr };
private:
    ButtonMashingEvent() {FUNCLOG};
    ~ButtonMashingEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// 選択イベント
class SelectEvent : public GameEvent
{
private:
    using SelectCallBack = pair<int, GameEvent*>;
public:
    CREATE_FUNC_WITH_PARAM(SelectEvent, rapidjson::Value&)
private:
    string message {};
    vector<string> choices {};
    vector<SelectCallBack> eventCallBacks {};
private:
    SelectEvent() {FUNCLOG};
    ~SelectEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

#endif /* defined(__LastSupper__MessageEvent__) */
