//
//  DungeonSceneManager.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#ifndef __LastSupper__DungeonSceneManager__
#define __LastSupper__DungeonSceneManager__

#include "Common.h"

#include "Datas/MapObject/EnemyData.h"

class DungeonScene;
class TiledMapLayer;
class MapObject;
class MapObjectList;
class EventFactory;
class EventScript;
class EventScriptValidator;
class Party;
class GameEvent;
class Enemy;
class StopWatch;

// ダンジョンシーンのマップ間で共有すべき情報を持つシングルトンクラス
class DungeonSceneManager
{
// クラスメソッド
public:
    static DungeonSceneManager* getInstance();
    static void destroy();
    
// インスタンス変数
private:
    EventFactory* eventFactory { nullptr };
    EventScriptValidator* scriprtValidator { nullptr };
    Sprite* cover { nullptr };
    vector<SummonData> summonDatas {};
    StopWatch* stopWatch {nullptr};
    
// インスタンスメソッド
private:
    DungeonSceneManager();                                                  // コンストラクタ
    ~DungeonSceneManager();                                                 // デストラクタ
    DungeonSceneManager(const DungeonSceneManager& other) {};               // コピーコンストラクタ
    DungeonSceneManager &operator = (const DungeonSceneManager& other);     // 代入演算子
public:
    DungeonScene* getScene() const;
    TiledMapLayer* getMapLayer() const;
    MapObjectList* getMapObjectList() const;
    EventFactory* getEventFactory() const;
    EventScriptValidator* getScriptValidator() const;
    EventScript* getEventScript() const;
    Party* getParty() const;
    
    // Scene
    void fadeOut(const Color3B& color, const float duration, function<void()> callback);
    void fadeIn(const float duration, function<void()> callback);
    
    // TiledMaplayer
    Size getMapSize() const;
    void addMapObject(MapObject* mapobject);
    void addEnemy(Enemy* enemy);
    
    // Director
    void changeMap(const Location& location, const int initEventId);
    
    // EventListener
    bool isPressed(const Key& key);
    vector<Key> getPressedCursorKeys() const;
    
    // Enemy
    vector<SummonData> getSummonDatas() const;
    
    // EventTask
    void runEvent(const int eventId);
    void pushEventBack(const int eventId);
    void pushEventFront(const int eventId);
    void pushEventBack(GameEvent* event);
    void pushEventFront(GameEvent* event);
    void runEventQueue();
    bool existsEvent() const;
    int getRunningEventId() const;
    int getPushingEventid() const;
    
    // PlayerControlTask
    void setPlayerControlEnable(bool enable);
    
    // StopWatch
    StopWatch* getStopWatch();
    void releaseStopWatch();
    void pauseStopWatch();
    void startStopWatch();
};

#endif /* defined(__LastSupper__DungeonSceneManager__) */
