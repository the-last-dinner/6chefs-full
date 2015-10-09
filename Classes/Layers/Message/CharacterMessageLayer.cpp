//
//  CharacterMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "Layers/Message/CharacterMessageLayer.h"

// 定数
const float CharacterMessageLayer::TOP_MARGIN { 50 };
const float CharacterMessageLayer::LEFT_MARGIN {60};
const float CharacterMessageLayer::H_MARGIN_S {30};

// コンストラクタ
CharacterMessageLayer::CharacterMessageLayer(){FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer(){FUNCLOG}

// 初期化
bool CharacterMessageLayer::init(const queue<Information>& infos)
{
    FUNCLOG
    if(!baseMessageLayer::init()) return false;
    
    this->infos = infos;
    this->pages = infos.front().pages;
    
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
    Information info {this->infos.front()};
	if(info.charaId != -1 && info.imgId != -1){
	// キャラクター画像;
//		Sprite* img { Sprite::createWithSpriteFrameName(CsvDataManager::getInstance()->getFileName(CsvDataManager::DataType::CHARACTER, info.charaId) + "_s_" + to_string(info.imgId) + ".png")};
//		img->setScale(WINDOW_HEIGHT * 0.8f / img->getContentSize().height);
//		img->setPosition(Point(WINDOW_WIDTH / 4, img->getContentSize().height / 2));
//		img->setLocalZOrder(-1);
//		this->addChild(img);
	}
	// キャラクター名
	this->nameFrame->removeAllChildren();
	Label* name { Label::createWithTTF((info.charaId == -1 || info.charaName != "")?info.charaName:CsvDataManager::getInstance()->getDisplayName(CsvDataManager::DataType::CHARACTER, info.charaId), this->fontPath, 26.f)};
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

// すべてのページを表示し終えた時
void CharacterMessageLayer::onAllPageDisplayed()
{
    if(this->infos.size() == 1)
    {
        this->close();
    }
    else
    {
        this->infos.pop();
        this->pages = this->infos.front().pages;
        this->message->setVisible(false);
        this->removeChild(this->message);
        this->_isAllLetterDisplayed = false;
        this->_isAllPageDisplayed = false;
        this->start();
    }
}