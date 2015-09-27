//
//  CharacterMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "Layers/Message/CharacterMessageLayer.h"

// コンストラクタ
CharacterMessageLayer::CharacterMessageLayer(){FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer(){FUNCLOG}

// キャラクターIDを指定して、画像・名前を表示する用create関数
CharacterMessageLayer* CharacterMessageLayer::createWithCharaId(const int& charaId, const int& imgDiffId, const queue<string>& pages)
{
	CharacterMessageLayer* pRet { CharacterMessageLayer::create(pages)};
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
	CharacterMessageLayer* pRet {CharacterMessageLayer::create(pages)};
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
	CharacterMessageLayer* pRet { CharacterMessageLayer::create(pages)};
	// 基本create関数の戻り値がnullptrではない時のみの処理
	if(pRet) pRet->setCharacterName(name);
	return pRet;
}

// 初期化
bool CharacterMessageLayer::init(const queue<string>& pages)
{
	FUNCLOG
	if(!Layer::init()) return false;
	if(!baseMessageLayer::init()) return false;
	
	// ページをセット
	this->setPages(pages);
	
	// メッセージ用枠を生成
	Sprite* mainFrame {Sprite::createWithSpriteFrameName("cm_frame.png")};
	Size mFrameSize = mainFrame->getContentSize();
	mainFrame->setPosition(Point(WINDOW_WIDTH / 2, mFrameSize.height / 2 + 10)); // 30は縦方向の調整用
	mainFrame->setLocalZOrder(0);
	mainFrame->setCascadeOpacityEnabled(true);
	this->setFrame(mainFrame);
	this->addChild(frame);
	
	// キャラクター名用枠を生成
	this->nameFrame = ui::Scale9Sprite::createWithSpriteFrameName("cm_frame_s.png", Rect(20, 0, 220, 68));
	this->nameFrame->setCascadeOpacityEnabled(true);
	this->addChild(this->nameFrame);
	
	this->setCascadeOpacityEnabled(true);
	
	return true;
}

// 文字の表示位置、キャラクター画像の関係でオーバーライド
void CharacterMessageLayer::createMessage()
{
	if(this->charaId != -1){
	// キャラクター画像;
		Sprite* img { Sprite::createWithSpriteFrameName(CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::CHARACTER, this->charaId) + "_s_" + to_string(this->imgDiffId) + ".png")};
		img->setScale(WINDOW_HEIGHT * 0.8f / img->getContentSize().height);
		img->setPosition(Point(WINDOW_WIDTH / 4, img->getContentSize().height / 2));
		img->setLocalZOrder(-1);
		this->addChild(img);
	}
	// キャラクター名
	this->nameFrame->removeAllChildren();
	Label* name { Label::createWithTTF((this->charaId == -1 && this->charaName != "")?this->charaName:CsvDataManager::getInstance()->getDisplayName(CsvDataManager::DataType::CHARACTER, this->charaId), this->fontPath, 26.f)};
	this->nameFrame->addChild(name);
	
	// キャラクター名の長さによってキャラクター名用枠の大きさ、位置を変える
	this->nameFrame->setContentSize(Size(name->getContentSize().width + H_MARGIN_S * 2, this->nameFrame->getContentSize().height));
	this->nameFrame->setPosition(this->nameFrame->getContentSize().width / 2 + LEFT_MARGIN / 4, this->frame->getContentSize().height + this->nameFrame->getContentSize().height / 2);

	name->setPosition(this->nameFrame->getContentSize() / 2);
	
	// メッセージ本文
	this->message = Label::createWithTTF(this->pages.front(), this->fontPath, this->fontSize);
	this->message->setHorizontalAlignment(this->h_alignment);
	this->message->setVerticalAlignment(this->v_alignment);
	this->message->setPosition(Point(this->message->getContentSize().width / 2 + LEFT_MARGIN, this->frame->getContentSize().height - this->message->getContentSize().height / 2 - TOP_MARGIN));
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