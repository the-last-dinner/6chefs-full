#include "ActionKey.h"

using namespace cocos2d;

bool ActionKey::init()
{
	if (!Layer::init()){
		return false;
	}
	initKeyState();
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ActionKey::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(ActionKey::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void ActionKey::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			this->keyStatus[Key::UP] = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->keyStatus[Key::DOWN] = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->keyStatus[Key::LEFT] = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->keyStatus[Key::RIGHT] = true;
			break;
		case EventKeyboard::KeyCode::KEY_X:
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->keyStatus[Key::MENU] = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->keyStatus[Key::DASH] = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->keyStatus[Key::SPACE] = true;
			break;
		default:
			break;
	}
}

void ActionKey::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			this->keyStatus[Key::UP] = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->keyStatus[Key::DOWN] = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->keyStatus[Key::LEFT] = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->keyStatus[Key::RIGHT] = false;
			break;
		case EventKeyboard::KeyCode::KEY_X:
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->keyStatus[Key::MENU] = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->keyStatus[Key::DASH] = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->keyStatus[Key::SPACE] = false;
			break;
		default:
			break;
	}
}

void ActionKey::initKeyState()
{
	this->keyStatus[Key::UP] = false;
	this->keyStatus[Key::DOWN] = false;
	this->keyStatus[Key::LEFT] = false;
	this->keyStatus[Key::RIGHT] = false;
	this->keyStatus[Key::MENU] = false;
	this->keyStatus[Key::DASH] = false;
	this->keyStatus[Key::SPACE] = false;
}

bool ActionKey::isPressed(Key key)
{
	return this->keyStatus.at(key);
}