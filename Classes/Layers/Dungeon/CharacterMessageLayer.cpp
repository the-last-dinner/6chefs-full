//
//  CharacterMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "CharacterMessageLayer.h"

// コンストラクタ
CharacterMessageLayer::CharacterMessageLayer():
charaId(-1),
charaName("")
{FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer()
{FUNCLOG}

// 基本となるcreate関数(内部的に呼ぶのみ)
CharacterMessageLayer* CharacterMessageLayer::createWithPages(const queue<string>& pages)
{
	CharacterMessageLayer* pRet = dynamic_cast<CharacterMessageLayer*>(baseMessageLayer::create(pages));
	return pRet;
}

// キャラクターIDを指定して、画像・名前を表示する用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithCharaId(const int& charaId, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::createWithPages(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet) pRet->setCharacterId(charaId);
	return pRet;
}

// キャラクターIDを指定して画像のみ表示し、名前は別途指定する用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithName(const int& charaId, const string& name, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::createWithPages(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet)
	{
		pRet->setCharacterId(charaId);
		pRet->setCharacterName(name);
	}
	return pRet;
}

// キャラクターの名前のみを表示させる用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithName(const string& name, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::createWithPages(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet) pRet->setCharacterName(name);
	return pRet;
}


// 初期化
bool CharacterMessageLayer::init()
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// 枠を生成
	Sprite* frame = Sprite::create();
	frame->setTextureRect(Rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT / 5));
	frame->setColor(Color3B::BLACK);
	frame->setPosition(WINDOW_CENTER);
	this->setFrame(frame);
	this->addChild(frame);
	
	// メッセージの表示位置をセット
	this->setMessagePosition(frame->getContentSize() / 2);
	
	return true;
}

// キャラクターメッセージレイヤーでは、ページ毎にキャラクター画像を入れ替える必要性があるのでオーバーライド
void CharacterMessageLayer::display()
{this->displayMessage();}

// キャラクター名をセット
void CharacterMessageLayer::setCharacterName(const string& name)
{this->charaName = name;}

// キャラクターIDをセット
void CharacterMessageLayer::setCharacterId(const int& charaId)
{this->charaId = charaId;}