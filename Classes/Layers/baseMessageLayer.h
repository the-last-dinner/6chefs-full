//
//  baseMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __BASE_MESSAGE_LAYER_H__
#define __BASE_MESSAGE_LAYER_H__

#include "Common.h"

class baseMessageLayer : public Layer
{
	// クラス変数
protected:
	static const float SPAN;
	
	// インスタンスメソッド
protected:
	baseMessageLayer();
	~baseMessageLayer();
	virtual void onSpacePressed();
public:
	virtual void displayMessage(const string& str, int fontSize = 24);
	
	// インスタンス変数
protected:
	EventListenerKeyboard* eventListener;
	string str;
	Sprite* base;
	Label* message;
	vector<Action*> letterActions;
};

#endif // __BASE_MESSAGE_LAYER_H__
