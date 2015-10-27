//
//  LoadingLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#include "Layers/LoadingLayer.h"

// コンストラクタ
LoadingLayer::LoadingLayer(){FUNCLOG}

// デストラクタ
LoadingLayer::~LoadingLayer(){FUNCLOG}

// 初期化
bool LoadingLayer::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	// plistを読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(TextureManager::basePath + "load.plist");
	
	// ローディングイメージを生成
	for(int i = 0 ; i < 2 ; i++)
	{
		Sprite* circle {Sprite::createWithSpriteFrameName("circle.png")};
		circle->setPosition(Point(WINDOW_WIDTH - circle->getContentSize().width / 4, circle->getContentSize().height / 4));
		circle->setScale(0.1f);
		circle->setOpacity(0);
	
		this->addChild(circle);
	
		// アクション生成
	
		ActionInterval* loadingAnimation = Sequence::create(DelayTime::create(0.5f * i),
													TargetedAction::create(circle, FadeIn::create(0.1f)),
													Spawn::create(TargetedAction::create(circle, FadeOut::create(1.f + i)),
                                                                  TargetedAction::create(circle, EaseCubicActionOut::create(ScaleTo::create(1.f + i, 0.5f))),
																  nullptr),
													TargetedAction::create(circle, ScaleTo::create(0.1f, 0.1f)),
													nullptr);
		
		this->runAction(RepeatForever::create(loadingAnimation));
	}
	return true;
}

// ロード完了時の処理
void LoadingLayer::loadFinished(const function<void()>& callback)
{
	FUNCLOG
	this->setCascadeOpacityEnabled(true);
	this->runAction(Sequence::create(FadeOut::create(0.8f), CallFunc::create([=]()
    {
		this->setVisible(false);
		this->removeAllChildren();
		callback();
		this->removeFromParent();
    }), nullptr));
}