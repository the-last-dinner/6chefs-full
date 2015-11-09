//
//  MapObjectEvent.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/25.
//
//

#ifndef __LastSupper__MapObjectEvent__
#define __LastSupper__MapObjectEvent__

#include "Event/GameEvent.h"

class MapObject;

// マップオブジェクトに関わるイベント
// 基底クラス
class MapObjectEvent : public GameEvent
{
// インスタンス変数
protected:
    string objectId {};
    
// インスタンスメソッド
protected:
    MapObjectEvent() {};
    ~MapObjectEvent() {};
    virtual bool init(rapidjson::Value& json);
};

// リアクション
class ReactionEvent : public MapObjectEvent
{
public:
    CREATE_FUNC_WITH_PARAM(ReactionEvent, rapidjson::Value&)
private:
    ReactionEvent() {FUNCLOG};
    ~ReactionEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

// マップオブジェクトを生成
class CreateMapObjectEvent : public MapObjectEvent
{
public:
    CREATE_FUNC_WITH_PARAM(CreateMapObjectEvent, rapidjson::Value&)
private:
    CreateMapObjectEvent() {FUNCLOG};
    ~CreateMapObjectEvent() {FUNCLOG};
    virtual bool init(rapidjson::Value& json);
    virtual void run() override;
};

#endif /* defined(__LastSupper__MapObjectEvent__) */
