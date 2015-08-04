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
imgDiffId(0),
charaName("")
{FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer()
{FUNCLOG}

// キャラクターIDを指定して、画像・名前を表示する用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithCharaId(const int& charaId, const int& imgDiffId, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::create(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet){
		pRet->setCharacterId(charaId);
		pRet->setImgDiffId(imgDiffId);
	}
	return pRet;
}

// キャラクターIDを指定して画像のみ表示し、名前は別途指定する用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithName(const int& charaId, const int& imgDiffId, const string& name, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::create(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet)
	{
		pRet->setCharacterId(charaId);
		pRet->setImgDiffId(imgDiffId);
		pRet->setCharacterName(name);
	}
	return pRet;
}

// キャラクターの名前のみを表示させる用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithName(const string& name, const queue<string>& pages)
{
	CharacterMessageLayer* pRet = CharacterMessageLayer::create(pages);
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet) pRet->setCharacterName(name);
	return pRet;
}


// 初期化
bool CharacterMessageLayer::init(const queue<string>& pages)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// ページをセット
	this->setPages(pages);
	
	// 枠を生成
	Sprite* frame = Sprite::createWithSpriteFrameName("cm_frame.png");
	Size frameSize = frame->getContentSize();
	frame->setPosition(Point(WINDOW_WIDTH / 2, frameSize.height / 2 + 10)); // 30は縦方向の調整用
	frame->setZOrder(0);
	this->setFrame(frame);
	this->addChild(frame);
	
	return true;
}

// 文字の表示位置、キャラクター画像の関係でオーバーライド
void CharacterMessageLayer::createMessage()
{
	if(this->charaId != -1){
	// キャラクター画像
		Sprite* img = Sprite::createWithSpriteFrameName(CharacterData::datas.at(this->charaId).at(static_cast<int>(CharacterData::DataType::TexturePrefix)) + "_s_" + to_string(this->imgDiffId) + ".png");
		img->setScale(WINDOW_HEIGHT * 0.8f / img->getContentSize().height);
		img->setPosition(Point(WINDOW_WIDTH / 4, img->getContentSize().height / 2));
		img->setZOrder(-1);
		this->addChild(img);
	}
	// キャラクター名
	Label* name = Label::createWithTTF((this->charaId == -1 && this->charaName != "")?this->charaName:CharacterData::datas.at(this->charaId).at(static_cast<int>(CharacterData::DataType::Name)), "fonts/cinecaption2.28.ttf", 26.f);
	name->setPosition(Point(name->getContentSize().width / 2 + this->frame->getContentSize().width / 10, this->frame->getContentSize().height * 0.83f - name->getContentSize().height / 2));
	this->frame->addChild(name);
	
	// メッセージ本文
	this->message = Label::createWithTTF(this->pages.front(), this->fontPath, this->fontSize);
	this->message->setHorizontalAlignment(this->h_alignment);
	this->message->setVerticalAlignment(this->v_alignment);
	this->message->setPosition(Point(this->message->getContentSize().width / 2 + this->frame->getContentSize().width / 10, this->frame->getContentSize().height * 0.65f - this->message->getContentSize().height / 2));
	this->frame->addChild(this->message);
}

// キャラクター名をセット
void CharacterMessageLayer::setCharacterName(const string& name)
{this->charaName = name;}

// キャラクターIDをセット
void CharacterMessageLayer::setCharacterId(const int& charaId)
{this->charaId = charaId;}

// キャラクター画像差分IDをセット
void CharacterMessageLayer::setImgDiffId(const int& imgDiffId)
{this->imgDiffId = imgDiffId;}