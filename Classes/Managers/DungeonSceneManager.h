//
//  DungeonSceneManager.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/04.
//
//

#ifndef __LastSupper__DungeonSceneManager__
#define __LastSupper__DungeonSceneManager__

#include "define.h"

class DungeonScene;
class TiledMapLayer;
class MapObjectList;
class EventFactory;
class EventListenerKeyboardLayer;
class EventScript;
class EventScriptValidator;
class Party;

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
    Party* party { nullptr };
    
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
    EventListenerKeyboardLayer* getSceneEventListener() const;
    EventScriptValidator* getScriptValidator() const;
    EventScript* getEventScript() const;
    Party* getParty() const;
    
    // EventListener
    void setInputCheckInterval(const float interval);
    void setEventListenerPaused(const bool paused);
    bool isPressed(const Key& key);
    
    // EventTask
    void runEvent(const int eventId);
    void pushEventBack(const int eventId);
    void pushEventFront(const int eventId);
    void runEventQueue();
    bool existsEvent();
};

#endif /* defined(__LastSupper__DungeonSceneManager__) */
