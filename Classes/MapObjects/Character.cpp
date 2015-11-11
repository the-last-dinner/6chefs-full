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
    this->charaId = charaId;
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
            AnimationCache::getInstance()->addAnimation(pAnimation, this->texturePrefix + to_string(i) + to_string(k));
        }
	}
	return true;
}

// キャラクタIDを取得
int Character::getCharacterId() const {return this->charaId;}

// 現在キャラが向いている方向を取得
Direction Character::getDirection() const {return this->direction;}

// キャラクターの向きを変える
void Character::setDirection(Direction direction)
{
	// 画像差し替え
	this->character->setSpriteFrame(this->texturePrefix + "_" + to_string(static_cast<int>(direction)) + "_0.png");
	
	// 向いている方向を更新
	this->direction = direction;
}

// 足踏み
void Character::stamp(const Direction direction, const int gridNum, float ratio)
{
    this->character->stopAllActions();
    
    Vector<FiniteTimeAction*> stampingActions {};
    
    for(int i { 0 }; i < gridNum; i++)
    {
        Animation* anime = AnimationCache::getInstance()->getAnimation(this->texturePrefix + to_string(static_cast<int>(this->direction)) + ((this->stampingRightFoot)?"1":"0"));
        this->stampingRightFoot = !this->stampingRightFoot;
        anime->setDelayPerUnit(DURATION_MOVE_ONE_GRID / ratio);
        
        stampingActions.pushBack(Animate::create(anime));
    }
    
    if(stampingActions.empty()) return;
    
    this->character->runAction(Sequence::create(stampingActions));
    this->character->runAction(Sequence::createWithTwoActions(DelayTime::create((DURATION_MOVE_ONE_GRID * gridNum) / ratio), CallFunc::create([this, direction]{this->setDirection(this->direction);})));
}

// 方向とマス数してで歩行させる
void Character::walkBy(const Direction& direction, const int gridNum, function<void()> onWalked, const float ratio)
{
    MapObject::moveBy(direction, gridNum, onWalked, ratio);
    this->stamp(this->direction, gridNum, ratio);
}

// 方向とマス数指定で歩行させる
void Character::walkBy(const vector<Direction>& directions, const int gridNum, function<void()> onWalked, const float ratio)
{
    MapObject::moveBy(directions, gridNum, onWalked, ratio);
    this->stamp(this->direction, gridNum, ratio);
}
