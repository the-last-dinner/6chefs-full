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
	void setCallback(const function<void()> callback);
protected:
	baseMenuLayer();
	~baseMenuLayer();
	virtual bool init(int sizeX, int sizeY);
	virtual void moveCursor(bool sound) = 0;
	virtual void onSpacePressed() = 0;
	virtual int getSelectedIndex();
	int getMenuSizeX();
	int getMenuSizeY();
	
private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
protected:
	vector<Node*> menuObjects;
	EventListenerKeyboard* eventListener;
private:
	int indexX;
	int indexY;
	int sizeX;
	int sizeY;
	function<void()> callback;
};

#endif // __BASE_MENU_LAYER_H__
