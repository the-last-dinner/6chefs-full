//
//  baseMenuLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#ifndef __BASE_MENU_LAYER_H__
#define __BASE_MENU_LAYER_H__

#include "Common.h"

class baseMenuLayer : public Layer
{
	// インスタンスメソッド
public:
	baseMenuLayer();
	~baseMenuLayer();
protected:
	virtual bool init(const function<void(bool)>& moveCursor, const function<void()>& onSpacePressed);
private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
protected:
	int indexX;
	int indexY;
	int sizeX;
	int sizeY;
	vector<string> menuStrings;
	EventListenerKeyboard* eventListener;
	function<void(bool)> moveCursor;
	function<void()> onSpacePressed;
	
};

#endif // __BASE_MENU_LAYER_H__
