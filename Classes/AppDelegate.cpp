#include "AppDelegate.h"
#include  "TitleScene.h"

// コンストタクタ
// シングルトンクラスのインスタンスを生成しておく
AppDelegate::AppDelegate()
{
	FUNCLOG
    EventScriptManager::getInstance();
	ActionKeyManager::getInstance();
	SoundManager::getInstance();
	this->init();
}

// デストラクタ
// メモリリークを防ぐため、シングルトンクラスのインスタンスを破棄する
AppDelegate::~AppDelegate() 
{
	FUNCLOG
    EventScriptManager::destroy();
	ActionKeyManager::destroy();
	SoundManager::destory();
}

// 初期化関連
void AppDelegate::init()
{
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
	director->runWithScene(TitleScene::createScene());
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
