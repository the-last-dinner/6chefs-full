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
	// インスタンスメソッド
protected:
	baseMessageLayer();
	~baseMessageLayer();
	virtual void onSpacePressed();
public:
	virtual void start();
	void addPage(const string& page);
	void setCallback(const function<void()>& callback);
protected:
	void setFontFilePath(const string& fontPath);
	void setFontSize(const int& fontSize);
	void setSpan(const float& span);
	void setVAlignment(const int& v_alignment);
	void setPages(const queue<string>& pages);
	void setFrame(Sprite* frame);
	void setMessagePosition(const Point& m_position);
private:
	virtual void popPage();
	virtual void disp();
	virtual void end();
	virtual void allLetterDisplayed();
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener;
	queue<string> pages;
	string fontPath;
	int fontSize;
	float span;
	int v_alignment;
	Point m_position;
	Sprite* frame;
	Label* message;
	vector<Action*> letterActions;
	function<void()> callback;
	bool _isAllLetterDisplayed;
	bool _isAllPageDisplayed;
};

#endif // __BASE_MESSAGE_LAYER_H__
