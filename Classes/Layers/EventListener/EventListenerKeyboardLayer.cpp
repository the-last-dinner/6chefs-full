//
//  EventListenerKeyboardLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/23.
//
//

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// 定数
// キー変換用連想配列
const map<EventKeyboard::KeyCode, Key> EventListenerKeyboardLayer::keyMap =
{
    {EventKeyboard::KeyCode::KEY_UP_ARROW, Key::UP},
    {EventKeyboard::KeyCode::KEY_W, Key::UP},
    {EventKeyboard::KeyCode::KEY_DOWN_ARROW, Key::DOWN},
    {EventKeyboard::KeyCode::KEY_S, Key::DOWN},
    {EventKeyboard::KeyCode::KEY_LEFT_ARROW, Key::LEFT},
    {EventKeyboard::KeyCode::KEY_A, Key::LEFT},
    {EventKeyboard::KeyCode::KEY_RIGHT_ARROW, Key::RIGHT},
    {EventKeyboard::KeyCode::KEY_D, Key::RIGHT},
    {EventKeyboard::KeyCode::KEY_X, Key::MENU},
    {EventKeyboard::KeyCode::KEY_UNDERSCORE, Key::MENU},
    {EventKeyboard::KeyCode::KEY_SHIFT, Key::DASH},
    {EventKeyboard::KeyCode::KEY_SPACE, Key::SPACE},
};

// コンストラクタ
EventListenerKeyboardLayer::EventListenerKeyboardLayer()
{ FUNCLOG }

// デストラクタ
EventListenerKeyboardLayer::~EventListenerKeyboardLayer()
{ FUNCLOG }

// 初期化
bool EventListenerKeyboardLayer::init()
{
    if(!Layer::init()) return false;
    
    EventListenerKeyboard* listenerKeyboard { EventListenerKeyboard::create() };
    listenerKeyboard->onKeyPressed = CC_CALLBACK_1(EventListenerKeyboardLayer::onKeyPressed, this);
    listenerKeyboard->onKeyReleased = CC_CALLBACK_1(EventListenerKeyboardLayer::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
    this->listenerKeyboard = listenerKeyboard;
    
    return true;
}

// リスナを有効/無効化
void EventListenerKeyboardLayer::setEnabled(bool enabled)
{
    this->listenerKeyboard->setEnabled(enabled);
}

// キーを押した時
void EventListenerKeyboardLayer::onKeyPressed(const EventKeyboard::KeyCode& keyCode)
{
    Key key {this->convertKeyCode(keyCode)};
    if(key == Key::SIZE) return;
    this->keyStatus[key] = true;
    switch (key) {
        case Key::UP:
        case Key::DOWN:
        case Key::LEFT:
        case Key::RIGHT:
            if(this->onCursorKeyPressed) this->onCursorKeyPressed(key);
            this->pressingKeys.push_back(key);
            // 方向キーを押した時は、入力チェック用にスケジューリング
            if(this->isScheduled(CC_SCHEDULE_SELECTOR(EventListenerKeyboardLayer::updatePressingKey))) this->unschedule(CC_SCHEDULE_SELECTOR(EventListenerKeyboardLayer::updatePressingKey));
            this->schedule(CC_SCHEDULE_SELECTOR(EventListenerKeyboardLayer::updatePressingKey), this->interval, CC_REPEAT_FOREVER, this->delay);
            break;
            
        case Key::SPACE:
            if(this->onSpaceKeyPressed) this->onSpaceKeyPressed();
            break;
            
        case Key::MENU:
            if(this->onMenuKeyPressed) this->onMenuKeyPressed();
            break;
            
        case Key::DASH:
            if(this->onDashKeyPressed) this->onDashKeyPressed();
            break;
            
        default:
            break;
    }
}

// キーを離した時
void EventListenerKeyboardLayer::onKeyReleased(const EventKeyboard::KeyCode& keyCode)
{
    Key key {this->convertKeyCode(keyCode)};
    if(key == Key::SIZE) return;
    this->keyStatus[key] = false;
    if(find(this->pressingKeys.begin(), this->pressingKeys.end(), key) != this->pressingKeys.end()) this->pressingKeys.erase(remove(this->pressingKeys.begin(), this->pressingKeys.end(), key));
    if(this->pressingKeys.empty()) this->unschedule(CC_SCHEDULE_SELECTOR(EventListenerKeyboardLayer::updatePressingKey));
}

// キーを押し続けている時
void EventListenerKeyboardLayer::updatePressingKey(float duration)
{
    if(this->pressingKey) this->pressingKey(this->pressingKeys.back());
}

// キーコードを変換。ゲームで使わないキーが与えられた場合はSIZEを返す
Key EventListenerKeyboardLayer::convertKeyCode(const EventKeyboard::KeyCode& keyCode)
{return (keyMap.count(keyCode) == 0)?Key::SIZE:keyMap.at(keyCode);}

// 指定のキーが押し状態か判別
bool EventListenerKeyboardLayer::isPressed(const Key& key)
{
    if(this->keyStatus.count(key) == 0) return false;
    return this->keyStatus[key];
}

// 現在主人公が進んでいる方向と、新たに押されたキーから、移動方向を返す
Direction EventListenerKeyboardLayer::getMoveDirection(const Direction& direction, const Key& key)
{
    return static_cast<Direction>(key);
}

