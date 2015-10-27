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
class ChangeMap : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(ChangeMap, rapidjson::Value&)
private:
    PlayerDataManager::Location location {};
private:
    virtual bool init(rapidjson::Value& json);
    virtual void run();
};

// カメライベント
class CameraEvent : public GameEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CameraEvent, rapidjson::Value&)
private:
    virtual bool init(rapidjson::Value& json);
    virtual void run();
};

#endif /* defined(__LastSupper__SceneEvent__) */
