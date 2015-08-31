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
public:
	void start();
	void addPage(const string& page);
	void setCallback(const function<void()>& callback);
	void setFontFilePath(const string& fontPath);
	void setFontSize(const int& fontSize);
	void setSpan(const float& span);
	void setVAlignment(const TextVAlignment& v_alignment);
	void setHAlignment(const TextHAlignment& h_alignment);
protected:
	baseMessageLayer();
	~baseMessageLayer();
	virtual bool init();
	void onSpacePressed();
	void setPages(const queue<string>& pages);
	void setFrame(Sprite* frame);
	virtual void displayMessage();
private:
	virtual void createMessage();
	virtual void nextPage();
	virtual void end();
	virtual void allLetterDisplayed();
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener { nullptr };
	float span { 0.05f };
	vector<Action*> letterActions {};
	function<void()> callback { nullptr };
	bool _isAllLetterDisplayed { false };
	bool _isAllPageDisplayed { false };
protected:
	Sprite* frame { nullptr };
	Label* message { nullptr };
	queue<string> pages {};
	string fontPath {"fonts/cinecaption2.28.ttf"};
	int fontSize { 24 };
	TextVAlignment v_alignment { TextVAlignment::TOP };
	TextHAlignment h_alignment { TextHAlignment::LEFT };
};

#endif // __BASE_MESSAGE_LAYER_H__
