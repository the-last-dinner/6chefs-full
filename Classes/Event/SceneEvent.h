//
//  SceneEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#ifndef __LastSupper__SceneEvent__
#define __LastSupper__SceneEvent__

#include "Event/GameEvent.h"

// マップ移動イベント
class ChangeMapEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(ChangeMapEvent, rapidjson::Value&)
private:
    Location location {};
    int initEventId { etoi(EventID::UNDIFINED) };
private:
    ChangeMapEvent() {FUNCLOG};
    ~ChangeMapEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run();
};

// カメライベント
class CameraEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CameraEvent, rapidjson::Value&)
private:
    CameraEvent() {FUNCLOG};
    ~CameraEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run();
};

// waitイベント
class WaitEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(WaitEvent, rapidjson::Value&)
private:
    float duration {0.f};
private:
    WaitEvent() {FUNCLOG};
    ~WaitEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// FadeOutイベント
class FadeOutEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(FadeOutEvent, rapidjson::Value&)
private:
    Color3B color { Color3B::BLACK };
    float duration { 0.5f };
private:
    FadeOutEvent() {FUNCLOG};
    ~FadeOutEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// FadeInイベント
class FadeInEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(FadeInEvent, rapidjson::Value&)
private:
    float duration { 0.5f };
private:
    FadeInEvent() {FUNCLOG};
    ~FadeInEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// CountDownイベント
class CountDownEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CountDownEvent, rapidjson::Value&)
private:
    float second { 5.f };
    int sEventId { static_cast<int>(EventID::UNDIFINED) };
    int fEventId { static_cast<int>(EventID::UNDIFINED) };
    rapidjson::Document doc { nullptr };
    GameEvent* sEvent { nullptr };
    GameEvent* fEvent { nullptr };
    GameEvent* event { nullptr };
private:
    CountDownEvent() {FUNCLOG};
    ~CountDownEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// StopCountイベント
class StopCountEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(StopCountEvent, rapidjson::Value&);
private:
    StopCountEvent() {FUNCLOG};
    ~StopCountEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};


#endif /* defined(__LastSupper__SceneEvent__) */
