#pragma once
#include "cocos2d.h"
class ActionKey : public cocos2d::Layer
{
public:
	ActionKey();
	~ActionKey();
	bool init();
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	CREATE_FUNC(ActionKey);
};