#include "ActionKey.h"

using namespace cocos2d;

static ActionKey * _action_key_instance;

ActionKey * ActionKey::getInstance()
{
	if (!_action_key_instance){
		_action_key_instance = ActionKey::create();
	}
	return _action_key_instance;
}


bool ActionKey::init()
{
	if (!Layer::init()){
		return false;
	}
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ActionKey::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(ActionKey::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void ActionKey::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	//cocos2d::log("Key with keycode %d pressed", keycode);
	switch (keycode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->UP = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->DOWN = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->LEFT = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->RIGHT = true;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			this->UP = true;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			this->DOWN = true;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			this->LEFT = true;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			this->RIGHT = true;
			break;
		case EventKeyboard::KeyCode::KEY_X:
			this->MENU = true;
			break;
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->MENU = true;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->DASH = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
			this->DASH = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->SPACE = true;
			break;
		default:
			break;
	}
}

void ActionKey::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	//cocos2d::log("Key with keycode %d released", keycode);
	switch (keycode){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			this->UP = false;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			this->DOWN = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			this->LEFT = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			this->RIGHT = false;
			break;
		case EventKeyboard::KeyCode::KEY_W:
			this->UP = false;
			break;
		case EventKeyboard::KeyCode::KEY_S:
			this->DOWN = false;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			this->LEFT = false;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			this->RIGHT = false;
			break;
		case EventKeyboard::KeyCode::KEY_X:
			this->MENU = false;
			break;
		case EventKeyboard::KeyCode::KEY_UNDERSCORE:
			this->MENU = false;
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_SHIFT:
			this->DASH = false;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_SHIFT:
			this->DASH = false;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			this->SPACE = false;
			break;
		default:
			break;
	}
}

bool ActionKey::isPressedUP()
{
	return this->UP;
}

bool ActionKey::isPressedDOWN()
{
	return this->DOWN;
}

bool ActionKey::isPressedLEFT()
{
	return this->LEFT;
}

bool ActionKey::isPressedRIGHT()
{
	return this->RIGHT;
}

bool ActionKey::isPressedDASH()
{
	return this->DASH;
}

bool ActionKey::isPressedMENU()
{
	return this->MENU;
}

bool ActionKey::isPressedSPACE()
{
	return this->SPACE;
}