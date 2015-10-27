//
//  TaskMediator.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#include "Tasks/TaskMediator.h"

#include "Scenes/DungeonScene.h"
#include "Layers/Dungeon/TiledMapLayer.h"

#include "Tasks/EventScriptTask.h"
#include "Tasks/ControlMainCharacterTask.h"
#include "Tasks/CameraTask.h"

#include "MapObjects/MapObjectList.h"
#include "MapObjects/Character.h"

// コンストラクタ
TaskMediator::TaskMediator() {FUNCLOG};

// デストラクタ
TaskMediator::~TaskMediator()
{
    FUNCLOG

    CC_SAFE_RELEASE_NULL(this->cameraTask);
    CC_SAFE_RELEASE_NULL(this->eventScriptTask);
    CC_SAFE_RELEASE_NULL(this->controlMainCharacterTask);
};

// 初期化
bool TaskMediator::init(DungeonScene* scene)
{
    if(!scene) return false;
    
    this->scene = scene;
    
    // カメラ処理クラスを生成
    CameraTask* cameraTask {CameraTask::create(this)};
    CC_SAFE_RETAIN(cameraTask);
    this->cameraTask = cameraTask;
    
    cameraTask->setTarget(scene->objectList->getMainCharacter());
    
    // イベントスクリプト処理クラスを生成
    EventScriptTask* eventScriptTask {EventScriptTask::create(this)};
    CC_SAFE_RETAIN(eventScriptTask);
    this->eventScriptTask = eventScriptTask;
    
    // 主人公操作処理クラスを生成
    ControlMainCharacterTask* controlMainCharacterTask {ControlMainCharacterTask::create(this)};
    CC_SAFE_RETAIN(controlMainCharacterTask);
    this->controlMainCharacterTask = controlMainCharacterTask;
    
    return true;
}

// シーン上でアクションを実行する
void TaskMediator::runOnScene(Action* action)
{
    this->scene->runAction(action);
}

// シーン上に子ノードを追加する
void TaskMediator::addChildToScene(Node* child)
{
    this->scene->addChild(child);
}

// シーンを取得
DungeonScene* TaskMediator::getScene() const
{
    return this->scene;
}

// オブジェクトリストを取得
MapObjectList* TaskMediator::getMapObjectList() const
{
    return this->scene->objectList;
}

#pragma mark -
#pragma mark CameraTask

// マップサイズを取得
Size TaskMediator::getMapSize() const
{
    return this->scene->mapLayer->getMapSize();
}

// マップの位置を設定
void TaskMediator::setMapPosition(const Point& position)
{
    this->scene->mapLayer->setPosition(position);
}

#pragma mark -
#pragma mark EventScriptTask

// イベントスクリプト実行
void TaskMediator::runEventScript(const int eventId)
{
    if(eventId == static_cast<int>(EventID::UNDIFINED)) return;
    this->eventScriptTask->runEventScript(eventId);
}

#pragma mark -
#pragma mark ControlMainCharacterTask

// 方向キーを押した時
void TaskMediator::onCursorKeyPressed(const Key key)
{
    this->controlMainCharacterTask->turn(MapUtils::keyToDirection(key));
}

// スペースキーを押した時
void TaskMediator::onSpaceKeyPressed()
{
    this->controlMainCharacterTask->search();
}

// キーを押し続けている時
void TaskMediator::intervalInputCheck(const vector<Key>& keys)
{
    this->controlMainCharacterTask->walking(MapUtils::keyToDirection(keys));
}

// イベントリスナを取得
EventListenerKeyboardLayer* TaskMediator::getEventListener() const
{
    return this->scene->listener;
}