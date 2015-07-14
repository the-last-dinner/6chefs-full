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
eventListener(nullptr),
mapLayer(nullptr)
{FUNCLOG}

// デストラクタ
DungeonScene::~DungeonScene()
{
	FUNCLOG
	delete this->data;
}

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
	
	// データクラスを初期化
	baseScene::data = new DungeonSceneData("TestScript");
	
	return baseScene::init(CC_CALLBACK_0(DungeonScene::loadFinished, this));
}

// リソースプリロード完了時の処理
void DungeonScene::loadFinished()
{
	FUNCLOG
	// 黒い幕を張っておく
	Sprite* black = Sprite::create();
	black->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
	black->setColor(Color3B::BLACK);
	black->setZOrder(static_cast<int>(Priority::SCREEN_EFFECT));
	black->setPosition(WINDOW_CENTER);
	this->addChild(black);
	
	// イベントリスナ生成
	this->eventListener = EventListenerKeyboard::create();
	this->eventListener->onKeyPressed = CC_CALLBACK_1(DungeonScene::onKeyPressed, this);
	this->eventListener->onKeyReleased = CC_CALLBACK_1(baseScene::onKeyReleased, this);
	
	// イベントリスナ登録
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->eventListener, this);
	
	// マップレイヤーを生成
	this->mapLayer = dynamic_cast<TiledMapLayer*>(TiledMapLayer::create("MAIN-Syokudou1", this->eventListener));
	this->addChild(mapLayer);
	
	// 黒い幕をフェードアウト
	this->runAction(Sequence::create(TargetedAction::create(black, FadeOut::create(0.3f)),
									 CallFunc::create([=](){black->removeFromParent();}),
									 nullptr));
	return;
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
		case::ActionKeyManager::Key::DOWN:
		case::ActionKeyManager::Key::LEFT:
		case::ActionKeyManager::Key::RIGHT:
		case::ActionKeyManager::Key::UP:
		case ActionKeyManager::Key::SPACE:
			this->mapLayer->controlMainCharacter(key);
			break;
		default:
			break;
	}
	return;
}