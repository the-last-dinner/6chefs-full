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
const float Character::DURATION_FOR_ONE_STEP = 0.1f;

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
bool Character::init(int charaId, const Direction direction)
{
	FUNCLOG
	if(!Node::init()) return false;
	// 生成時の情報をセット
	this->direction = direction;
    this->texturePrefix = CsvDataManager::getInstance()->getCharaFileName(charaId);
	
    // プロパティリストが存在するか確認。存在しなければfalseを返す（生成しない）
    string fullPath { FileUtils::getInstance()->fullPathForFilename(basePath + this->texturePrefix + ".plist") };
    
    if(fullPath.size() == 0) return false;
    
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

// 足踏み
void Character::stamp(const Direction direction, float ratio)
{
    this->character->stopAllActions();
    
    // 現在の向きのアニメーションを取得
    Animation* anime = AnimationCache::getInstance()->getAnimation(to_string(static_cast<int>(this->direction)) + ((this->stampingRightFoot)?"1":"0"));
    this->stampingRightFoot = !this->stampingRightFoot;
    anime->setDelayPerUnit(DURATION_FOR_ONE_STEP / ratio);
    
    this->character->runAction(Animate::create(anime));
    this->character->runAction(Sequence::createWithTwoActions(DelayTime::create(DURATION_FOR_ONE_STEP), CallFunc::create([this, direction](){this->setDirection(direction);})));
}

// 移動ベクトルから歩行アクションを生成
ActionInterval* Character::createWalkByAction(const Point& vector , float ratio)
{
    if(vector == Point::ZERO) return nullptr;
    
    return TargetedAction::create(this, Spawn::create(CallFunc::create([this](){this->setMoving(true); this->stamp(this->direction);}), MoveBy::create(DURATION_FOR_ONE_STEP / ratio, vector), Sequence::createWithTwoActions(DelayTime::create(DURATION_FOR_ONE_STEP / ratio), CallFunc::create([this](){this->setMoving(false);})), nullptr));
}

// 一方向から歩行アクション生成
ActionInterval* Character::createWalkByAction(const Direction direction, float ratio)
{
    return this->createWalkByAction(MapUtils::getGridVector(direction), ratio);
}

// 二方向から歩行アクション生成
ActionInterval* Character::createWalkByAction(const Direction directions[2], float ratio)
{
    Point movementVector {Point::ZERO};
    for(int i {0};i < 2; i++)
    {
        movementVector += MapUtils::getGridVector(directions[i]);
    }
    
    return this->createWalkByAction(movementVector);
}