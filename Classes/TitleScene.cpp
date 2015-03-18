#include "TitleScene.h"

using namespace cocos2d;

TitleScene::TitleScene()
{

}

TitleScene::~TitleScene()
{

}

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
	this->gsManager = GameStatusManager::getInstance();
	this->actionKey = ActionKey::create();
	auto titleMenu = TitleMenu::create();
	this->addChild(this->actionKey);
	this->addChild(titleMenu);
	this->scheduleUpdate();
	return true;
}

void TitleScene::update(float delta)
{	
	switch (this->gsManager->getCurrentGameState())
	{
		case GameState::WAIT:
		break;

		case GameState::TITLE_MAIN:
			//ˆ—
			if (this->actionKey->isPressed(Key::UP, 1)){
				log("delta : %f", delta);
			}
		break;
		case GameState::TITLE_LOAD:
			//ˆ—
		break;
	}
	this->actionKey->updateKeyState();
}
