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
	auto layer = ActionKey::create();
	scene->addChild(layer);
	
	return scene;
}

bool TitleScene::init()
{
	if(!Scene::init()){
		return false;
	}
	return true;
}