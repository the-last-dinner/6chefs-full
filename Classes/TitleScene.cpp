#include "TitleScene.h"

using namespace cocos2d;
Scene * TitleScene::createScene()
{
	log("METHOD createScene CALLED");
	auto scene = Scene::create();
	auto actionKeyLayer = ActionKey::getInstance();
	auto mainLayer = TitleScene::create();
	log("actionKeyLayer: %p", actionKeyLayer);
	scene->addChild(mainLayer);
	scene->addChild(actionKeyLayer);
	return scene;
}

bool TitleScene::init()
{
	log("METHOD init CALLED");
	if(!Layer::init()){
		return false;
	}
	this->scheduleUpdate();
	this->actionKey = ActionKey::getInstance();
	return true;
}

void TitleScene::update(float delta)
{	
	if (this->actionKey->isPressedDOWN()){
		log("DOWNKEY PRESSED");
	}
}
