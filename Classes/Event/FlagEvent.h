//
//  FlagEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/27.
//
//

#ifndef __LastSupper__FlagEvent__
#define __LastSupper__FlagEvent__

#include "Event/GameEvent.h"

// 実行中IDのイベントを発動させないようにする
class NeverAgainEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(NeverAgainEvent, rapidjson::Value&)
private:
    int eventId {static_cast<int>(EventID::UNDIFINED)};
private:
    NeverAgainEvent() {FUNCLOG};
    ~NeverAgainEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// アイテムを入手する
class GetItemEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(GetItemEvent, rapidjson::Value&)
private:
    int itemId { 0 };
private:
    GetItemEvent() {FUNCLOG};
    ~GetItemEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

#endif /* defined(__LastSupper__FlagEvent__) */
