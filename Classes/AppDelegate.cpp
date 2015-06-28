#include "AppDelegate.h"
#include  "LoadScene.h"

// コンストタクタ
// シングルトンクラスのインスタンスを生成しておく
AppDelegate::AppDelegate()
{
	FUNCLOG
    PlayerDataManager::getInstance();
    EventScriptManager::getInstance();
	GameStatusManager::getInstance();
	ActionKeyManager::getInstance();
	TiledMapManager::getInstance();
	SoundManager::getInstance();
	this->init();
}

// デストラクタ
// メモリリークを防ぐため、シングルトンクラスのインスタンスを破棄する
AppDelegate::~AppDelegate() 
{
	FUNCLOG
    EventScriptManager::destroy();
	GameStatusManager::destroy();
	ActionKeyManager::destroy();
	TiledMapManager::destory();
	SoundManager::destory();
    PlayerDataManager::destroy();
}

// 初期化関連
void AppDelegate::init()
{
	TiledMapManager::getInstance()->setBasePath("map/");
	SoundManager::getInstance()->setBasePath("se/", "bgm/");
    EventScriptManager::getInstance()->setEventScript("TestScript");
	return;
}

bool AppDelegate::applicationDidFinishLaunching()
{
	FUNCLOG
	auto director = Director::getInstance();
	auto glView = director->getOpenGLView();
	if (!glView) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
		glView = GLViewImpl::createWithRect("My Game", Rect(0, 0, WINDOW_WIDTH , WINDOW_HEIGHT));
#else	
		glView = GLViewImpl::create("My Game");
#endif
		director->setOpenGLView(glView);
	}
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);
	director->runWithScene(LoadScene::createScene(SceneType::TITLE));
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
}
