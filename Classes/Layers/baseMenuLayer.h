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
	virtual void show() = 0;
	virtual void hide() = 0;
protected:
	baseMenuLayer();
	~baseMenuLayer();
	virtual bool init(const Point& index, const Size& size);
	virtual bool init(int sizeX, int sizeY);
	virtual void onIndexChanged(int newIdx, bool sound = true) = 0;
	virtual void onSpacePressed(int idx) = 0;
	virtual void onMenuKeyPressed() = 0;
	virtual int getSelectedIndex() const;
	int getMenuSizeX() const;
	int getMenuSizeY() const;
private:
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
protected:
	vector<Node*> menuObjects {};
	EventListenerKeyboard* eventListener { nullptr };
private:
	int indexX { 0 };
	int indexY { 0 };
	int sizeX { 0 };
	int sizeY { 0 };
};

#endif // __BASE_MENU_LAYER_H__
