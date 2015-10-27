//
//  EventScriptValidator.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/24.
//
//

#ifndef __LastSupper__EventScriptValidator__
#define __LastSupper__EventScriptValidator__

#include "Common.h"

class DungeonScene;
class GameEvent;
class MapObjectList;
class TaskMediator;
class MapObject;
class TiledMapLayer;

// イベントスクリプトの値チェック、変換を担うクラス
class EventScriptValidator : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(EventScriptValidator, TaskMediator*)
    
// インスタンス変数
private:
    TaskMediator* mediator { nullptr };
    
// インスタンスメソッド
private:
    EventScriptValidator();
    ~EventScriptValidator();
    bool init(TaskMediator* mediator);
    
    // condition
    bool detectEquipFlg(rapidjson::Value& json, bool negative);
    bool detectEventFlg(rapidjson::Value& json, bool negative);
    bool detectFlg(rapidjson::Value& json, bool negative);
    bool detectItemFlg(rapidjson::Value& json, bool negative);
    bool detectStatusFlg(rapidjson::Value& json, bool negative);
    
public:
    bool hasMember(rapidjson::Value& json, const char* member);
    bool detectCondition(rapidjson::Value& json);
    
    MapObject* getMapObjectById(rapidjson::Value& json);
    template<typename T>
    inline T getMapObjectById(rapidjson::Value& json) { return dynamic_cast<T>(this->getMapObjectById(json)); };
    
    Point getPoint(rapidjson::Value& json);
    Direction getDirection(rapidjson::Value& json);
    
    DungeonScene* getScene() const;
    TiledMapLayer* getMapLayer() const;
    MapObjectList* getMapObjectList() const;
    Size getMapSize() const;
};
#endif /* defined(__LastSupper__EventScriptValidator__) */
