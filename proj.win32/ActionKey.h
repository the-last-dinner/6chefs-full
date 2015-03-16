#ifndef  _ACTION_KEY_H_
#define _ACTION_KEY_H_
#include "cocos2d.h"
#include "Common.h"

class ActionKey : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(ActionKey);
	bool isPressedUP();
	bool isPressedDOWN();
	bool isPressedLEFT();
	bool isPressedRIGHT();
	bool isPressedMENU();
	bool isPressedDASH();
	bool isPressedSPACE();
	static ActionKey * getInstance();
private:
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event * event);
	bool UP = false;
	bool DOWN = false;
	bool LEFT = false;
	bool RIGHT = false;
	bool MENU = false;
	bool DASH = false;
	bool SPACE = false;
};

#endif // _ACTION_KEY_H_