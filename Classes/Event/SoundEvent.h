//
//  SoundEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#ifndef __LastSupper__SoundEvent__
#define __LastSupper__SoundEvent__

#include "Event/GameEvent.h"

// BGM再生イベント
class PlayBGM : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(PlayBGM, rapidjson::Value&)
private:
    string fileName {};
private:
    PlayBGM():fileName("") {FUNCLOG};
    ~PlayBGM() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// SE再生イベント
class PlaySE : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(PlaySE, rapidjson::Value&)
private:
    string fileName {};
private:
    PlaySE():fileName("") {FUNCLOG};
    ~PlaySE() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};


#endif /* defined(__LastSupper__SoundEvent__) */
