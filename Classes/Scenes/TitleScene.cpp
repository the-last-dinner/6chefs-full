#include "TitleScene.h"

// メニュー初期化
const vector<string> TitleScene::menuStrings =
{
	"はじめから",
	"終了",
};

// コンストラクタ
TitleScene::TitleScene():
eventListener(),
menuCounter(0)
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
	
	// メニューを生成
	int menuSize = 32;
	for(int i = 0; i < menuStrings.size(); i++)
	{
		Label* menu = Label::createWithSystemFont(menuStrings.at(i), "Arial", menuSize);
		menu->setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - (menuSize + 20) * i);
		menu->setTag(i);
		menu->setTextColor(Color4B::RED);
		menu->enableOutline(Color4B::BLACK, 5);
		menu->setOpacity(0);
		this->addChild(menu);
		
		menu->runAction(Sequence::create(DelayTime::create(1.f * i),
										 Spawn::create(MoveBy::create(2.f, Vec2(0, -20)), FadeIn::create(2.f), nullptr),
										nullptr));
	}
	
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
	
	// 選択されているメニューに照準を当てる
	this->moveCursor();
	
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

// カーソルを移動
void TitleScene::moveCursor()
{
	FUNCLOG
	for(int i = 0; i < menuStrings.size(); i++)
	{
		Node* menu = this->getChildByTag(i);
		this->runAction(Spawn::create(TargetedAction::create(menu, ScaleTo::create(0.2f, (this->menuCounter % static_cast<int>(MenuType::SIZE) == i)?1.1f:1.f)),
									  TargetedAction::create(menu, TintTo::create(0.5f, 255, 255, 255)),
									  nullptr));
	}
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
			if(this->menuCounter > 0) menuCounter--;
			break;
		case ActionKeyManager::Key::DOWN:
			this->menuCounter++;
			break;
		case ActionKeyManager::Key::SPACE:
			this->pressSpaceKey();
			break;
		default:
			break;
	}
	this->moveCursor();
	return;
}

// 決定キーを押した時
void TitleScene::pressSpaceKey()
{
	FUNCLOG
	MenuType type = static_cast<MenuType>(this->menuCounter % static_cast<int>(MenuType::SIZE));
	switch (type) {
		case MenuType::BEGINING:
			Director::getInstance()->replaceScene(LoadScene::createScene(SceneType::OPENING));
			break;
		case MenuType::FINISH:
			Director::getInstance()->end();
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