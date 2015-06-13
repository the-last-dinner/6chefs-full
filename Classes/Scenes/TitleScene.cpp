#include "TitleScene.h"

// コンストラクタ
TitleScene::TitleScene():
eventListener()
{FUNCLOG}

// デストラクタ
TitleScene::~TitleScene()
{FUNCLOG}

// シーン生成
Scene* TitleScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* mainLayer = TitleScene::create();
	scene->addChild(mainLayer);
	return scene;
}

// 初期化
bool TitleScene::init()
{
	if(!Layer::init()) return false;
	
	//タイトル画像をキャッシュから生成
	Sprite* titleBg = Sprite::createWithSpriteFrameName("title.png");
	titleBg->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	titleBg->setOpacity(0);
	this->addChild(titleBg);
	
	// イベントリスナ生成。無効にしておく。
	this->eventListener = EventListenerKeyboard::create();
	this->eventListener->onKeyPressed = CC_CALLBACK_1(TitleScene::onKeyPressed, this);
	this->eventListener->onKeyReleased = CC_CALLBACK_1(TitleScene::onKeyReleased, this);
	this->eventListener->setEnabled(false);
	
	// イベントリスナ登録
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(this->eventListener, this);
	
	// アニメーションをセット。全てのアニメーションが終わったらイベントリスナを有効にする。
	this->runAction(Sequence::create(TargetedAction::create(titleBg, FadeIn::create(2.f)),
									 CallFunc::create([this](){this->eventListener->setEnabled(true);}),
									 nullptr));
	// ループを開始
	this->scheduleUpdate();
	return true;
}

// ゲームループ
void TitleScene::update(float delta)
{
	ActionKeyManager::getInstance()->updateKeyStatus(delta);
	return;
}

// キーを押した時
void TitleScene::onKeyPressed(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 押し状態にする
	ActionKeyManager::getInstance()->pressKey(key);
	switch(key)
	{
		case ActionKeyManager::Key::UP:
			break;
		case ActionKeyManager::Key::DOWN:
			break;
		case ActionKeyManager::Key::SPACE:
			break;
		default:
			break;
	}
	return;
}

// キーを離した時
void TitleScene::onKeyReleased(EventKeyboard::KeyCode keyCode)
{
	FUNCLOG
	// cocos2d上のキーコードからゲーム内でのキーコードに変換
	ActionKeyManager::Key key = ActionKeyManager::getInstance()->convertKeyCode(keyCode);
	
	// 離し状態にする
	ActionKeyManager::getInstance()->releaseKey(key);
	return;
}