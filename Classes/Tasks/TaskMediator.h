//
//  TaskMediator.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#ifndef __LastSupper__TaskMediator__
#define __LastSupper__TaskMediator__

#include "Common.h"

class DungeonScene;
class EventListenerKeyboardLayer;

class CameraTask;
class EventScriptTask;
class ControlMainCharacterTask;

class MapObjectList;

// タスク仲介クラス
class TaskMediator : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(TaskMediator, DungeonScene*)

// インスタンス変数
private:
    DungeonScene* scene { nullptr };
    CameraTask* cameraTask { nullptr };
    EventScriptTask* eventScriptTask { nullptr };
    ControlMainCharacterTask* controlMainCharacterTask { nullptr };
    
// インスタンスメソッド
public:
    DungeonScene* getScene() const;
    MapObjectList* getMapObjectList() const;
    void runOnScene(Action* action);
    void addChildToScene(Node* child);
    
    // カメラ
    Size getMapSize() const;
    void setMapPosition(const Point& position);
    
    // イベントスクリプト
    void runEventScript(const int eventId);
    
    // 主人公操作
    void onCursorKeyPressed(const Key key);
    void onSpaceKeyPressed();
    void intervalInputCheck(const vector<Key>& keys);
    EventListenerKeyboardLayer* getEventListener() const;
    
private:
    TaskMediator();
    ~TaskMediator();
    bool init(DungeonScene* scene);
};

#endif /* defined(__LastSupper__TaskMediator__) */
