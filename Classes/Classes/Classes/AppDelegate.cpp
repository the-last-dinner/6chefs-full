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
		glView = GLViewImpl::create("My Game");
		director->setOpenGLView(glView);
	}
	director->setDisplayStats(true);
	director->setAnimationInterval(1.0 / 60);
	auto scene = TitleScene::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
}
