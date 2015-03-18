#include "TitleScene.h"
#include "view/title/TitleMenu.h"

using namespace cocos2d;
Scene * TitleScene::createScene()
{
	auto scene = Scene::create();
	auto mainLayer = TitleScene::create();
	scene->addChild(mainLayer);
	return scene;
}

bool TitleScene::init()
{
	if(!Layer::init()){
		return false;
	}
	this->actionKey = ActionKey::create();
	this->addChild(this->actionKey);
	auto titleMenu = TitleMenu::create();
	this->addChild(titleMenu);
	this->scheduleUpdate();
	return true;
}

void TitleScene::update(float delta)
{	
	if (this->actionKey->isPressed(Key::UP)){
		log("KEY STATUS UP");
	}
}
