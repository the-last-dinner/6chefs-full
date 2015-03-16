#include "AppDelegate.h"
#include  "TitleScene.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();
	auto glView = director->getOpenGLView();
	if (!glView) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
		glView = GLViewImpl::createWithRect("My Game", Rect(0, 0, WIDTH , HEIGHT ));
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

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
