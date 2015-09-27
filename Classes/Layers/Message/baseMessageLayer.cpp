//
//  baseMessageLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/07/12.
//
//

#include "Layers/Message/baseMessageLayer.h"

// コンストラクタ
baseMessageLayer::baseMessageLayer(){FUNCLOG}

// デストラクタ
baseMessageLayer::~baseMessageLayer(){FUNCLOG}

// 初期化
bool baseMessageLayer::init()
{
	FUNCLOG
    if(!Layer::init()) return false;
    
	// イベントリスナ生成
    EventListenerKeyboardLayer* listenerKeyboard {EventListenerKeyboardLayer::create()};
    listenerKeyboard->onSpaceKeyPressed = CC_CALLBACK_0(baseMessageLayer::onSpacePressed, this);
    this->addChild(listenerKeyboard);
    this->listenerKeyboard = listenerKeyboard;
	
	return true;
}

// spaceキーを押した時の処理
void baseMessageLayer::onSpacePressed()
{
	// すべてのページを表示し終えていた場合
	if(this->_isAllPageDisplayed){
		this->onAllPageDisplayed();
		return;
	}
	// ページ内ですべての文字を表示し終えていたら、次ページへ
	if(this->_isAllLetterDisplayed){
		this->nextPage();
	}else
	{
		// 表示できていなければ、全表示
		for(Action* letterAction : this->letterActions)
		{this->stopAction(letterAction);}
		for(int i = 0; i < this->message->getStringLength(); i++)
		{Sprite* letter = this->message->getLetter(i); if(letter) letter->setVisible(true);}
		this->_isAllLetterDisplayed = true;
		this->onAllLetterDisplayed();
		if(this->pages.size() == 1) this->_isAllPageDisplayed = true;
	}
	return;
}

// 表示を開始する
void baseMessageLayer::start()
{this->createMessage(); this->displayMessage();}

// ページ開始時に呼ばれるメソッド、メッセージの流れ方以外を変えたい場合はこちらをオーバーライドすべし
void baseMessageLayer::createMessage()
{
	this->message = Label::createWithTTF(this->pages.front(), this->fontPath, this->fontSize);
	this->message->setHorizontalAlignment(this->h_alignment);
	this->message->setVerticalAlignment(this->v_alignment);
	this->message->setPosition(this->frame->getContentSize() / 2);
	this->frame->addChild(this->message);
}

// メッセージを表示
void baseMessageLayer::displayMessage()
{
	// messageがnullptrなら終了
	if(!this->message) return;
	
	int stringLength = this->message->getStringLength();
	int lastLetterIndex = 0;
    
	// 改行文字をカウントしない最後の文字のインデックスを取得する
	for(int i = stringLength - 1; i >= 0; i--)
	{
		Sprite* letter = this->message->getLetter(i);
		if(letter){
			lastLetterIndex = i;
			break;
		}
	}

	// アニメーション設定
	for(int i = 0; i < stringLength; i++)
	{
		Sprite* letter = this->message->getLetter(i);
		// エスケープ文字をスルー
		if(letter)
		{
			letter->setVisible(false);
			Sequence* letterAction = Sequence::create(DelayTime::create(this->span * i), TargetedAction::create(letter, Show::create()), CallFunc::create([=](){if(i == lastLetterIndex){this->_isAllLetterDisplayed = true;this->onAllLetterDisplayed(); if(this->pages.size() == 1) this->_isAllPageDisplayed = true;}}), nullptr);
			this->letterActions.push_back(letterAction);
			this->runAction(letterAction);
		}
	}
}

// 改ページを行う
void baseMessageLayer::nextPage()
{
	FUNCLOG
	this->pages.pop();
	this->message->setVisible(false);
	this->removeChild(this->message);
	this->createMessage();
	this->displayMessage();
	return;
}

// すべてのページを表示し終えた時
void baseMessageLayer::onAllPageDisplayed()
{
    this->close();
}

// メッセージウインドウを閉じる
void baseMessageLayer::close()
{
	FUNCLOG
	this->setCascadeOpacityEnabled(true);
	this->listenerKeyboard->setEnabled(false);
	this->runAction(Sequence::createWithTwoActions(TargetedAction::create(this, FadeOut::create(0.2f)), CallFunc::create([=](){this->setVisible(false); this->removeFromParent();})));
	this->callback();
}

// 使用するフォントファイルのパスをセット
void baseMessageLayer::setFontFilePath(const string& fontPath)
{this->fontPath = fontPath;}

// 表示するフォントのサイズをセット
void baseMessageLayer::setFontSize(const int& fontSize)
{this->fontSize = fontSize;}

// 縦方向の位置をセット
void baseMessageLayer::setVAlignment(const TextVAlignment& v_alignment)
{this->v_alignment = v_alignment;}

// 横方向の位置をセット
void baseMessageLayer::setHAlignment(const TextHAlignment& h_alignment)
{this->h_alignment = h_alignment;}

// 文字表示の間隔をセット
void baseMessageLayer::setSpan(const float& span)
{this->span = span;}

// ページ群をセット
void baseMessageLayer::setPages(const queue<string>& pages)
{this->pages = pages;}

// ページを追加
void baseMessageLayer::addPage(const string& page)
{this->pages.push(page);}

// メッセージレイヤーの枠をセット
void baseMessageLayer::setFrame(Sprite* frame)
{this->frame = frame;}

// メッセージをすべて見終わった際に実行されるメソッドをセット
void baseMessageLayer::setCallback(const function<void()>& callback)
{this->callback = callback;}