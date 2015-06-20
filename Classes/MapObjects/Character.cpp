//
//  Character.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/15.
//
//

#include "Character.h"

// キャラクターのデータ(ID, プロパティリストのファイル名, 表示名)
const vector<vector<string>> Character::characterDatas =
{
	{"0", "magoichi", "孫一"},
};

// キャラのプロパティリストのディレクトリ
const string Character::basePath = "img/texture/character/";

// 1マス進むのにかかる時間(基準値)
const float Character::SECOND_PER_GRID = 0.2f;

// コンストラクタ
Character::Character():
character(nullptr),
texturePrefix(""),
charaType(),
direction(),
_isMoving(false),
pAnimation{nullptr},
identifier(false)
{FUNCLOG}

// デストラクタ
Character::~Character()
{
	FUNCLOG
	for(int i = 0; i < static_cast<int>(Character::Direction::SIZE); this->pAnimation[i][0]->release(), this->pAnimation[i][1]->release(),i++);
}

// create関数。この関数を用いてキャラクターを初期化
Character* Character::create(int charaId, CharacterType charaType, Direction direction)
{
	Character* pChara = new(nothrow)Character();
	if (pChara && pChara->init(charaId, charaType, direction))
	{
		// オブジェクトを自動メモリ管理へ登録
		pChara->autorelease();
		return pChara;
	}
	CC_SAFE_DELETE(pChara);
	return nullptr;
}

// 初期化
bool Character::init(int charaId, CharacterType charaType, Direction direction)
{
	FUNCLOG
	// 生成時の情報をセット
	this->charaType = charaType;
	this->direction = direction;
	this->texturePrefix = characterDatas.at(charaId).at(static_cast<int>(DataType::TexturePrefix));
	
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
			this->pAnimation[i][k] = Animation::create();
			
			// それぞれの向きのアニメーション用画像を追加していく、足踏みしていない画像を間にはさむ
			this->pAnimation[i][k]->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(i) + "_" + to_string(k + 1) + ".png"));
			this->pAnimation[i][k]->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(i) + "_0.png"));
			
			// 全フレーム表示し終えた時、１フレーム目に戻る
			this->pAnimation[i][k]->setRestoreOriginalFrame(true);
			
			// キャッシュに保存
			AnimationCache::getInstance()->addAnimation(this->pAnimation[i][k], to_string(i) + to_string(k));
		}
	}
	return true;
}

// キャラクターの向きを変える
void Character::setDirection(Direction direction)
{
	FUNCLOG
	// 画像差し替え
	this->character->setSpriteFrame(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) + "_0.png");
	
	// 向いている方向を更新
	this->direction = direction;
	return;
}

// 現在キャラが向いている方向を取得
Character::Direction Character::getDirection()
{
	FUNCLOG
	return this->direction;
}

// キャラが動いているかをセット
void Character::setMoving(bool _isMoving)
{
	FUNCLOG
	this->_isMoving = _isMoving;
	return;
}

// キャラが移動中かどうか取得
bool Character::isMoving()
{
	FUNCLOG
	return this->_isMoving;
}

// 動いているアニメーションを再生
void Character::move(float ratio)
{
	FUNCLOG
	// 動いていなければ
	if(!this->isMoving()){
		// 現在の向きのアニメーションを取得
		Animation* anime = AnimationCache::getInstance()->getAnimation(to_string(static_cast<int>(this->direction)) + ((this->identifier)?"0":"1"));
		this->identifier = (this->identifier)?false:true;
		anime->setDelayPerUnit(SECOND_PER_GRID * ratio);
		this->runAction(TargetedAction::create(this->character, Animate::create(anime)));
	}
	return;
}