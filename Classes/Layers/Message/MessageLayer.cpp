//
//  MessageLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/12.
//
//

#include "Layers/Message/MessageLayer.h"

#include "Datas/Message/MessageData.h"
#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// コンストラクタ
MessageLayer::MessageLayer() {FUNCLOG};

// デストラクタ
MessageLayer::~MessageLayer() {FUNCLOG};

// 初期化
bool MessageLayer::init(function<void()> onCloseCallback)
{
    FUNCLOG
    if(!Layer::init()) return false;
    
    this->onClose = onCloseCallback;
    
    // イベントリスナ生成
    EventListenerKeyboardLayer* listener {EventListenerKeyboardLayer::create()};
    listener->onSpaceKeyPressed = CC_CALLBACK_0(MessageLayer::onSpacekeyPressed, this);
    this->addChild(listener);
    this->listener = listener;
    
    this->setCascadeOpacityEnabled(true);
    
    // メッセージを生成して表示
    this->displayMessageWithAnimation(this->createMessage());
    
    return true;
}

// スペースキーを押した時
void MessageLayer::onSpacekeyPressed()
{
    // ページ内ですべての文字を表示し終えていたら
    if(this->allLetterDisplayed)
    {
        if(this->hasNextPage())
        {
            this->nextPage();
        }
        else
        {
            this->close();
        }
    }
    else
    {
        // 表示できていなければ、全表示
        this->displayMessage(this->message);
    }
}

// 文字を一文字ずつ表示
void MessageLayer::displayMessageWithAnimation(Label* message)
{
    // messageがnullptrなら終了
    if(!message) return;
    
    this->message = message;
    
    int stringLength = message->getStringLength();
    int lastLetterIndex { 0 };
    
    // 改行文字をカウントしない最後の文字のインデックスを取得する
    for(int i = stringLength - 1; i >= 0; i--)
    {
        Sprite* letter { this->message->getLetter(i) };
        if(letter){
            lastLetterIndex = i;
            break;
        }
    }
    
    // アニメーション設定
    for(int i = 0; i < stringLength; i++)
    {
        Sprite* letter { message->getLetter(i) };
        
        // エスケープ文字をスルー
        if(letter)
        {
            letter->setVisible(false);
            this->runAction(Sequence::createWithTwoActions(DelayTime::create(this->latency * i), TargetedAction::create(letter, Show::create())));
        }
    }
    this->runAction(Sequence::createWithTwoActions(DelayTime::create(stringLength * this->latency), CallFunc::create([this](){this->onAllLetterDisplayed();})));
}

// すべての文字を表示
void MessageLayer::displayMessage(Label* message)
{
    if(!message) return;
    
    for(int i = 0; i < message->getStringLength(); i++)
    {
        Sprite* letter { this->message->getLetter(i) };
        if(letter)
        {
            letter->stopAllActions();
            letter->setVisible(true);
        }
    }
    this->onAllLetterDisplayed();
}

// すべての文字を表示した時
void MessageLayer::onAllLetterDisplayed()
{
    this->allLetterDisplayed = true;
}

// 次のページへ
void MessageLayer::nextPage()
{
    this->removeChild(this->message);
    this->allLetterDisplayed = false;
    this->displayMessageWithAnimation(this->createMessage());
}

// メッセージレイヤを閉じる
void MessageLayer::close()
{
    FUNCLOG
    this->message->setCascadeOpacityEnabled(true);
    this->frame->setCascadeOpacityEnabled(true);
    this->listener->setEnabled(false);
    this->runAction(FadeOut::create(0.2f));
    if (this->onClose) this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.2f), CallFunc::create([this](){this->onClose(); this->removeFromParent();})));
}