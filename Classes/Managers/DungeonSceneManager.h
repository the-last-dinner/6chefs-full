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

class DungeonScene;
class TiledMapLayer;
class MapObject;
class MapObjectList;
class EventFactory;
class EventScript;
class EventScriptValidator;
class Party;
class GameEvent;

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
    
    // Director
    void changeMap(const Location& location);
    
    // EventListener
    bool isPressed(const Key& key);
    vector<Key> getPressedCursorKeys() const;
    
    // EventTask
    void runEvent(const int eventId);
    void pushEventBack(const int eventId);
    void pushEventFront(const int eventId);
    void pushEventBack(GameEvent* event);
    void pushEventFront(GameEvent* event);
    void runEventQueue();
    bool existsEvent() const;
    int getRunningEventId() const;
    
    // PlayerControlTask
    void setPlayerControlEnable(bool enable);
};

#endif /* defined(__LastSupper__DungeonSceneManager__) */
