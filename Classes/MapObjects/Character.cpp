//
//  Character.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/15.
//
//

#include "MapObjects/Character.h"

// キャラのプロパティリストのディレクトリ
const string Character::basePath = "img/character/";

// 一歩進むのにかかる時間(基準値)
const float Character::DURATION_FOR_ONE_STEP = 0.05f;

// コンストラクタ
Character::Character(){FUNCLOG}

// デストラクタ
Character::~Character(){FUNCLOG}

// create関数。この関数を用いてキャラクターを初期化
Character* Character::create(int charaId, Direction direction)
{
	Character* pChara = new(nothrow)Character();
	if (pChara && pChara->init(charaId, direction))
	{
		// オブジェクトを自動メモリ管理へ登録
		pChara->autorelease();
		return pChara;
	}
	CC_SAFE_DELETE(pChara);
	return nullptr;
}

// 初期化
bool Character::init(int charaId, Direction direction)
{
	FUNCLOG
	if(!Node::init()) return false;
	// 生成時の情報をセット
	this->direction = direction;
    this->texturePrefix = CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::CHARACTER, charaId);
	
	// プロパティリスト読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(basePath + this->texturePrefix + ".plist");
	
	// Spriteを生成
	this->character = Sprite::createWithSpriteFrameName(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) +"_0.png");
	this->addChild(this->character);
    
    // サイズ、衝突判定範囲をセット
    this->setContentSize(this->character->getContentSize());
    this->setCollisionRect(Rect(0, 0, this->getContentSize().width, this->getContentSize().height / 2));
	
    for(int i {0}; i < static_cast<int>(Direction::SIZE); i++)
	{
        Animation* pAnimation = Animation::create();
        
        // それぞれの向きのアニメーション用画像を追加していく
        for(int k {0}; k < 3; k++)
        {
            pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(i) + "_" + to_string(k) + ".png"));
        }
        
        // アニメーションを終了させた時点で最初のフレームヘ移動させる
        pAnimation->setRestoreOriginalFrame(true);
        
        // キャッシュに保存
        AnimationCache::getInstance()->addAnimation(pAnimation, this->texturePrefix + to_string(i));
	}
	return true;
}

// キャラクターの向きを変える
void Character::setDirection(Direction direction)
{
	// 画像差し替え
	this->character->setSpriteFrame(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) + "_0.png");
	
	// 向いている方向を更新
	this->direction = direction;
}

// 現在キャラが向いている方向を取得
Direction Character::getDirection()
{return this->direction;}

// キャラが動いているかをセット
void Character::setMoving(bool _isMoving)
{this->_isMoving = _isMoving;}

// キャラが移動中かどうか取得
bool Character::isMoving()
{return this->_isMoving;}

// 足踏みアニメーションを生成
ActionInterval* Character::createStampingAction(const Direction& direction, float ratio)
{
    if(this->isMoving()) return nullptr;
    
    this->setMoving(true);
    
	// 現在の向きのアニメーションを取得
	Animation* anime = AnimationCache::getInstance()->getAnimation(this->texturePrefix + to_string(static_cast<int>(direction)));
	anime->setDelayPerUnit(DURATION_FOR_ONE_STEP * ratio * 3);
    ActionInterval* stamping {TargetedAction::create(this->character, Animate::create(anime))};
    stamping->setTag(1);
    
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(anime->getDuration()), CallFunc::create([this](){this->setMoving(false);})));
    
    this->character->runAction(stamping);
    
    return stamping;
}

// 足踏みを止める
void Character::stopStamping()
{
    dynamic_cast<Animate*>(this->getActionByTag(1))->stop();
    
}

// 歩行アクションを生成
ActionInterval* Character::createWalkByAction(const Point& vector , float ratio)
{
    int gridNum {};
    return nullptr;
}
