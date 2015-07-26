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
	Layer* layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

// 初期化
bool TitleScene::init()
{
	if(!Layer::init()) return false;
	
	// データクラス初期化
	baseScene::data = new TitleSceneData();
	
	return baseScene::init();
}

// リソースロード終了後の処理
void TitleScene::loadFinished()
{
	FUNCLOG
	// メインメニューのレイヤーを生成
	TitleMainMenuLayer* mainMenuLayer = TitleMainMenuLayer::create();
	this->addChild(mainMenuLayer);
	
	return;
}