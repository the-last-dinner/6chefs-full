#include "AppDelegate.h"
#include "Scenes/TitleScene.h"

// コンストタクタ
// シングルトンクラスのインスタンスを生成しておく
AppDelegate::AppDelegate()
{
	FUNCLOG
    CsvDataManager::getInstance();
    PlayerDataManager::getInstance();
	SoundManager::getInstance();
	TextureManager::getInstance();
	this->init();
}

// デストラクタ
// メモリリークを防ぐため、シングルトンクラスのインスタンスを破棄する
AppDelegate::~AppDelegate() 
{
	FUNCLOG
    CsvDataManager::destroy();
	SoundManager::destory();
    PlayerDataManager::destroy();
	TextureManager::destory();
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
	// Tiledのチラつきを防止
	director->setProjection(Director::Projection::_2D);
	director->setDepthTest(false);
	
	// デバッグ表示
	director->setDisplayStats(true);
	
	// フレームレート
	director->setAnimationInterval(1.0 / 60);
	
	// シーンを指定してゲーム開始
	director->runWithScene(TitleScene::create());
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
