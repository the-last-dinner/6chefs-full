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
    PlayerDataManager::Location location {};
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

#endif /* defined(__LastSupper__SceneEvent__) */
