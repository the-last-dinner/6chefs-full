//
//  Character.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/15.
//
//

#include "MapObjects/Character.h"

// キャラのプロパティリストのディレクトリ
const string Character::basePath = "img/texture/character/";

// 1マス進むのにかかる時間(基準値)
const float Character::SECOND_PER_GRID = 0.05f;

// コンストラクタ
Character::Character():
character(nullptr),
texturePrefix(""),
direction(),
_isMoving(false),
identifier(false)
{FUNCLOG}

// デストラクタ
Character::~Character()
{FUNCLOG}

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
	this->texturePrefix = CharacterData::datas.at(charaId).at(static_cast<int>(CharacterData::DataType::TexturePrefix));
	
	// プロパティリスト読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(basePath + this->texturePrefix + ".plist");
	
	// Spriteを生成
	this->character = Sprite::createWithSpriteFrameName(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) +"_0.png");
	this->addChild(this->character);
	
	for(int i = 0; i < static_cast<int>(Direction::SIZE); i++)
	{
		// 右足だけ動くタイプと左足だけ動くタイプでアニメーションを分ける
		for(int k = 0; k < 2; k++)
		{
			Animation* pAnimation = Animation::create();
			
			// それぞれの向きのアニメーション用画像を追加していく
			pAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(i) + "_" + to_string(k + 1) + ".png"));
			
			// キャッシュに保存
			AnimationCache::getInstance()->addAnimation(pAnimation, to_string(i) + to_string(k));
		}
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
	return;
}

// 現在キャラが向いている方向を取得
Direction Character::getDirection()
{return this->direction;}

// キャラが動いているかをセット
void Character::setMoving(bool _isMoving)
{
	this->_isMoving = _isMoving;
	return;
}

// キャラが移動中かどうか取得
bool Character::isMoving()
{return this->_isMoving;}

// 動いているアニメーションを再生
void Character::stamp(float ratio)
{
	// 現在の向きのアニメーションを取得
	Animation* anime = AnimationCache::getInstance()->getAnimation(to_string(static_cast<int>(this->direction)) + ((this->identifier)?"0":"1"));
	this->identifier = (this->identifier)?false:true;
	anime->setDelayPerUnit(SECOND_PER_GRID * ratio);
	this->runAction(Sequence::create(CallFunc::create([=](){this->setMoving(true);}),
									 TargetedAction::create(this->character, Animate::create(anime)),
									 CallFunc::create([=](){this->setMoving(false);
															this->character->setDisplayFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(static_cast<int>(this->direction)) + "_0.png"));}),
									 nullptr));
	return;
}