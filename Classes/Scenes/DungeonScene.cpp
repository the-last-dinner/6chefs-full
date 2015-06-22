//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#include "DungeonScene.h"

const map<ActionKeyManager::Key, Point> DungeonScene::scrollMap =
{
	{ActionKeyManager::Key::DOWN, Point(0, -GRID)},
	{ActionKeyManager::Key::RIGHT, Point(GRID, 0)},
	{ActionKeyManager::Key::LEFT, Point(-GRID, 0)},
	{ActionKeyManager::Key::UP, Point(0, GRID)}
};

// コンストラクタ
DungeonScene::DungeonScene():
eventListener(nullptr)
{FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{FUNCLOG}

// シーン生成
Scene* DungeonScene::createScene()
{
	Scene* scene = Scene::create();
	DungeonScene* layer = DungeonScene::create();
	scene->addChild(layer);
	return scene;
}

// 初期化
bool DungeonScene::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// イベントリスナ生成
	this->eventListener = EventListenerKeyboard::create();
	this->eventListener->onKeyPressed = CC_CALLBACK_1(DungeonScene::onKeyPressed, this);
	this->eventListener->onKeyReleased = CC_CALLBACK_1(DungeonScene::onKeyReleased, this);
	
	// イベントリスナ登録
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->eventListener, this);
	
	// マップ生成
	experimental::TMXTiledMap* map = TiledMapManager::getInstance()->getTiledMap();
	map->setName("map");
	map->setPositionY(-100);
	this->addChild(map);
	
	// キャラクター生成
	Character* chara = Character::create(0, Character::CharacterType::MAIN, Character::Direction::FRONT);
	chara->setName("magoichi");
	chara->setGridPosition(Point(10, 10));
	map->addChild(chara);
	
	// ゲームループ開始
	this->scheduleUpdate();
    
    // EventScriptManagerにlayerを渡す
    EventScriptManager::getInstance()->setDungeonScene(this);
    
    //テストでイベントID:1を呼んでみる
    EventScriptManager::getInstance()->runEvent(1);
	return true;
}

// キーを押した時の処理
void DungeonScene::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
    //テストでイベントID:2を呼んでみる
    EventScriptManager::getInstance()->runEvent(2);
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 押し状態にする
	ActionKeyManager::getInstance()->pressKey(key);
	
	// MAPのポインタを取得
	experimental::TMXTiledMap* map = this->getChildByName<experimental::TMXTiledMap*>("map");
	
	switch(key)
	{
		case::ActionKeyManager::Key::DOWN:
		case::ActionKeyManager::Key::LEFT:
		case::ActionKeyManager::Key::RIGHT:
		case::ActionKeyManager::Key::UP:
		{
			Character* magoichi = map->getChildByName<Character*>("magoichi");
			
			// 主人公が移動中でない時のみ処理
			if(!magoichi->isMoving()){
				
				// 移動キーが押された時は、向きを変える
				magoichi->setDirection(static_cast<Character::Direction>(key));
				
				// スケジュールを開始
				this->schedule([=](float delta){
					if(ActionKeyManager::getInstance()->isPressed(key))
					{
						// 主人公が動いていない、かつその方向に当たり判定がなかったら
						if(!magoichi->isMoving() && !magoichi->isHit(static_cast<Character::Direction>(key)))
						{
							// 指定秒後に移動をさせる
							magoichi->move();
							this->runAction(Spawn::create(TargetedAction::create(map, MoveBy::create(Character::SECOND_PER_GRID, - scrollMap.at(key))),
														  TargetedAction::create(magoichi, MoveBy::create(Character::SECOND_PER_GRID, scrollMap.at(key))),
														  nullptr));
						}
					}
					else
					{
						// キーを離したらループを解除
						this->unschedule("PlayerControlCheck");
					}
				
				}, ActionKeyManager::INPUT_CHECK_SPAN, "PlayerControlCheck");

			}
			break;
		}
		case ActionKeyManager::Key::SPACE:
			break;
		default:
			break;
	}
	return;
}

// キーを離した時の処理
void DungeonScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);

	return;
}

// ゲームループ
void DungeonScene::update(float delta)
{
	return;
}