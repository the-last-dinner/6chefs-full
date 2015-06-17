//
//  Character.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/15.
//
//

#include "Character.h"

const vector<vector<string>> Character::characterDatas =
{
	{"0", "magoichi", "孫一"},
};

const string Character::basePath = "img/texture/character/";

// コンストラクタ
Character::Character():
character(nullptr),
texturePrefix(""),
charaType(),
currentDirection()
{
	FUNCLOG
	// 配列はイニシャライザで初期化できないのでコンストラクタ内
	for(int i = 0; i < static_cast<int>(Direction::SIZE); this->pAnimation[i] = nullptr, i++);
}

// デストラクタ
Character::~Character()
{FUNCLOG}

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
	this->currentDirection = direction;
	this->texturePrefix = characterDatas.at(charaId).at(static_cast<int>(DataType::TexturePrefix));
	
	// プロパティリスト読み込み
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(basePath + this->texturePrefix + ".plist");
	
	// Spriteを生成
	this->character = Sprite::createWithSpriteFrameName(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) +"_0.png");
	this->addChild(this->character);
	
	for(int i = 0; i < static_cast<int>(Direction::SIZE); i++)
	{
		this->pAnimation[i] = Animation::create();
		for(int j = 0; j < static_cast<int>(Direction::SIZE) - 1; j++)
		{
			// それぞれの向きのアニメーション用画像を追加していく
			this->pAnimation[i]->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(this->texturePrefix + "_" + to_string(i) + "_" + to_string(j) + ".png"));
		}
		// 画像切り替え周期
		this->pAnimation[i]->setDelayPerUnit(0.5f);
		
		// 全フレーム表示し終えた時、１フレーム目に戻る
		this->pAnimation[i]->setRestoreOriginalFrame(true);
		
		// キャッシュに保存
		AnimationCache::getInstance()->addAnimation(this->pAnimation[i], to_string(i));
	}
	return true;
}

// キャラクターの向きを変える
void Character::changeDirection(Direction direction)
{
	FUNCLOG
	this->character->setSpriteFrame(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) + "_0.png");
	return;
}