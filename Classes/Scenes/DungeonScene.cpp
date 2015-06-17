//
//  DungeonScene.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/14.
//
//

#include "DungeonScene.h"

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
	// イベントリスナ生成。無効にしておく。
	this->eventListener = EventListenerKeyboard::create();
	this->eventListener->onKeyPressed = CC_CALLBACK_1(DungeonScene::onKeyPressed, this);
	this->eventListener->onKeyReleased = CC_CALLBACK_1(DungeonScene::onKeyReleased, this);
	
	// イベントリスナ登録
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->eventListener, this);
	
	experimental::TMXTiledMap* map = TiledMapManager::getInstance()->getTiledMap();
	this->addChild(map);
	
	// キャラクター生成
	Character* chara = Character::create(0, Character::CharacterType::MAIN, Character::Direction::FRONT);
	chara->setName("magoichi");
	chara->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	this->addChild(chara);
	return true;
}

// キーを押した時の処理
void DungeonScene::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 押し状態にする
	ActionKeyManager::getInstance()->pressKey(key);
	switch(key)
	{
		case ActionKeyManager::Key::UP:
			this->getChildByName<Character*>("magoichi")->changeDirection(Character::Direction::BACK);
			break;
		case ActionKeyManager::Key::DOWN:
			this->getChildByName<Character*>("magoichi")->changeDirection(Character::Direction::FRONT);
			break;
		case ActionKeyManager::Key::LEFT:
			this->getChildByName<Character*>("magoichi")->changeDirection(Character::Direction::LEFT);
			break;
		case ActionKeyManager::Key::RIGHT:
			this->getChildByName<Character*>("magoichi")->changeDirection(Character::Direction::RIGHT);
			break;
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