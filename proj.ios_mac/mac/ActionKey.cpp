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
			this->keyStatus[Key::UP] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->keyStatus[Key::DOWN] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->keyStatus[Key::LEFT] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->keyStatus[Key::RIGHT] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_X:
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->keyStatus[Key::MENU] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->keyStatus[Key::DASH] = 1;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->keyStatus[Key::SPACE] = 1;
			break;
		default:
			break;
	}
	return;
}

void ActionKey::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	switch (keycode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			this->keyStatus[Key::UP] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			this->keyStatus[Key::DOWN] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			this->keyStatus[Key::LEFT] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			this->keyStatus[Key::RIGHT] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_X:
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->keyStatus[Key::MENU] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->keyStatus[Key::DASH] = 0;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->keyStatus[Key::SPACE] = 0;
			break;
		default:
			break;
	}
	return;
}

void ActionKey::initKeyState()
{	
	this->keyStatus[Key::UP] = 0;
	this->keyStatus[Key::DOWN] = 0;
	this->keyStatus[Key::LEFT] = 0;
	this->keyStatus[Key::RIGHT] = 0;
	this->keyStatus[Key::MENU] = 0;
	this->keyStatus[Key::DASH] = 0;
	this->keyStatus[Key::SPACE] = 0;
	return;
}

bool ActionKey::isPressed(Key key)
{	
	if (this->keyStatus.at(key) > 0){
		return true;
	}
	return false;
}

bool ActionKey::isPressed(Key key, int count)
{
	if (this->keyStatus.at(key) <= count && this->keyStatus.at(key) != 0){
		return true;
	}
	return false;
}

void ActionKey::updateKeyState()
{
	for (auto itr = this->keyStatus.begin(); itr != this->keyStatus.end(); ++itr)
	{	
		if (itr->second == 1 && itr->second < MAX_COUNT){
			itr->second ++;
		}
	}
	return;
}