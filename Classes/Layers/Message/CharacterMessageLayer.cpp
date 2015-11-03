//
//  CharacterMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#include "Layers/Message/CharacterMessageLayer.h"

#include "Datas/Message/CharacterMessageData.h"

// 定数
const float CharacterMessageLayer::TOP_MARGIN { 50 };
const float CharacterMessageLayer::LEFT_MARGIN {60};
const float CharacterMessageLayer::H_MARGIN_S {30};

// コンストラクタ
CharacterMessageLayer::CharacterMessageLayer(){FUNCLOG}

// デストラクタ
CharacterMessageLayer::~CharacterMessageLayer(){FUNCLOG}

// 初期化
bool CharacterMessageLayer::init(const queue<CharacterMessageData*>& datas, function<void()> onCloseCallback)
{
    FUNCLOG
    
    this->datas = datas;
    
    // メッセージ用枠を生成
    Sprite* mainFrame {Sprite::createWithSpriteFrameName("cm_frame.png")};
    Size mFrameSize = mainFrame->getContentSize();
    mainFrame->setPosition(Point(WINDOW_WIDTH / 2, mFrameSize.height / 2 + 10)); // 30は縦方向の調整用
    mainFrame->setLocalZOrder(0);
    mainFrame->setCascadeOpacityEnabled(true);
    this->addChild(mainFrame);
    this->frame = mainFrame;
    
    // キャラクター名用枠を生成
    this->nameFrame = ui::Scale9Sprite::createWithSpriteFrameName("cm_frame_s.png", Rect(20, 0, 220, 68));
    this->nameFrame->setCascadeOpacityEnabled(true);
    this->addChild(this->nameFrame);
    
    this->setCascadeOpacityEnabled(true);
    
    return MessageLayer::init(onCloseCallback);
}

// メッセージを生成
Label* CharacterMessageLayer::createMessage()
{
    CharacterMessageData* data {this->datas.front()};
	if(data->getCharaId() != -1 && data->getImgId() != -1){
	// キャラクター画像;
//		Sprite* img { Sprite::createWithSpriteFrameName(CsvDataManager::getInstance()->getCharaFileName(info.charaId) + "_s_" + to_string(info.imgId) + ".png")};
//		img->setScale(WINDOW_HEIGHT * 0.8f / img->getContentSize().height);
//		img->setPosition(Point(WINDOW_WIDTH / 4, img->getContentSize().height / 2));
//		img->setLocalZOrder(-1);
//		this->addChild(img);
	}
	// キャラクター名
	this->nameFrame->removeAllChildren();
	Label* name { Label::createWithTTF((data->getCharaId() == -1 || data->getCharaName() != "")?data->getCharaName():CsvDataManager::getInstance()->getCharaName(data->getCharaId()), "fonts/cinecaption2.28.ttf", 26.f)};
	this->nameFrame->addChild(name);
	
	// キャラクター名の長さによってキャラクター名用枠の大きさ、位置を変える
	this->nameFrame->setContentSize(Size(name->getContentSize().width + H_MARGIN_S * 2, this->nameFrame->getContentSize().height));
	this->nameFrame->setPosition(this->nameFrame->getContentSize().width / 2 + LEFT_MARGIN / 4, this->frame->getContentSize().height + this->nameFrame->getContentSize().height / 2);

	name->setPosition(this->nameFrame->getContentSize() / 2);
	
	// メッセージ本文
	Label* message = Label::createWithTTF(data->getMessage(), "fonts/cinecaption2.28.ttf", 24.f);
    message->setHorizontalAlignment(TextHAlignment::LEFT);
    message->setVerticalAlignment(TextVAlignment::TOP);
	message->setPosition(Point(message->getContentSize().width / 2 + LEFT_MARGIN, this->frame->getContentSize().height - message->getContentSize().height / 2 - TOP_MARGIN));
	this->frame->addChild(message);
    
    if(!this->datas.front()->hasNextPage())
    {
        CC_SAFE_RELEASE(this->datas.front());
        this->datas.pop();
    }

    return message;
}

// 次のページがあるか
bool CharacterMessageLayer::hasNextPage()
{
    return !this->datas.empty();
}