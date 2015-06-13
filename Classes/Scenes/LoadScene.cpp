//
//  LoadScene.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#include "LoadScene.h"

const string LoadScene::texturePath = "img/texture/";

const map<SceneType, string> LoadScene::textureNames =
{
	{SceneType::TITLE, "title_scene"},
};

// コンストラクタ
LoadScene::LoadScene():
nextSceneType()
{FUNCLOG}

// デストラクタ
LoadScene::~LoadScene()
{FUNCLOG}

// createScene関数
Scene* LoadScene::createScene(const SceneType& sceneType)
{
	Scene* scene = Scene::create();
	Layer* layer = LoadScene::create(sceneType);
	scene->addChild(layer);
	return scene;
}

// 初期化
bool LoadScene::init(const SceneType& sceneType)
{
	if(!Layer::init()) return false;
	
	// アクションキーを初期化
	ActionKeyManager::getInstance()->initKeyStatus();
	
	this->nextSceneType = sceneType;
	
	// plistを読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(this->texturePath + "load_scene.plist");
	
	// ローディングイメージを生成
	Sprite* circle = Sprite::createWithSpriteFrameName("circle.png");
	Sprite* circle2 = Sprite::createWithSpriteFrameName("circle.png");
	
	circle->setPosition(Point(WINDOW_WIDTH - circle->getContentSize().width / 4, circle->getContentSize().height / 4));
	circle->setScale(0.1f);
	circle->setOpacity(0);
	
	circle2->setPosition(Point(WINDOW_WIDTH - circle2->getContentSize().width / 4, circle2->getContentSize().height / 4));
	circle2->setScale(0.1f);
	circle2->setOpacity(0);
	
	this->addChild(circle);
	this->addChild(circle2);
	
	// アクション生成
	this->runAction(RepeatForever::create(Sequence::create(TargetedAction::create(circle, FadeIn::create(0.1f)),
														   Spawn::create(TargetedAction::create(circle, FadeOut::create(1.f)),
																		 TargetedAction::create(circle, ScaleTo::create(1.f, 0.5f)),
																		 nullptr),
														   TargetedAction::create(circle, ScaleTo::create(0.1f, 0.1f)),
														   nullptr)
										  )
					);
	
	
	this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f),
														   TargetedAction::create(circle2, FadeIn::create(0.1f)),
														   Spawn::create(TargetedAction::create(circle2, FadeOut::create(2.0f)),
																		 TargetedAction::create(circle2, ScaleTo::create(2.0f, 0.5f)),
																		 nullptr),
														   TargetedAction::create(circle2, ScaleTo::create(0.1f, 0.1f)),
														   nullptr)
										  )
					);
	
	this->resourceLoad();

	return true;
}

void LoadScene::resourceLoad()
{
	FUNCLOG
	if(nextSceneType != SceneType::TITLE) return;
	Director::getInstance()->getTextureCache()->addImageAsync(texturePath + textureNames.at(nextSceneType) + ".pvr.ccz",
	[this](Texture2D* loaded_texture){
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(texturePath + textureNames.at(nextSceneType) + ".plist", loaded_texture);
		this->loadFinished();
	});

// 別スレッドを生成
//	thread th = thread([this](){
//		Director::getInstance()->getScheduler()->performFunctionInCocosThread([this](){this->loadFinished();});
//	});
//	
//	// スレッドの管理を手放す
//	// スレッドの処理を待つ場合はt.join()かstd::asyncを使う
//	th.detach();
	return;
}

void LoadScene::loadFinished()
{
	FUNCLOG
	Scene* (* createSceneFuncs[])() = {
		TitleScene::createScene,
	};
	Director::getInstance()->replaceScene(createSceneFuncs[static_cast<int>(this->nextSceneType)]());
	return;
}
