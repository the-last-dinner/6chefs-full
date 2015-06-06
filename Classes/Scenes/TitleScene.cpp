#include "TitleScene.h"

// コンストラクタ
TitleScene::TitleScene()
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

bool TitleScene::init()
{
	if(!Layer::init()) return false;
	this->scheduleUpdate();
	return true;
}

void TitleScene::update(float delta)
{	
	
}
