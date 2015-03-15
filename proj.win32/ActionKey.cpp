#include "ActionKey.h"

using namespace cocos2d;

ActionKey::ActionKey()
{
}

ActionKey::~ActionKey()
{
}

bool ActionKey::init()
{
	if (!Layer::init()){
		return FALSE;
	}
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ActionKey::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(ActionKey::onKeyReleased, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return TRUE;
}

void ActionKey::onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	cocos2d::log("Key with keycode %d pressed", keycode);
}

void ActionKey::onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event)
{
	cocos2d::log("Key with keycode %d released", keycode);
}