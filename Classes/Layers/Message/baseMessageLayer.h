//
//  baseMessageLayer.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/07/12.
//
//

#ifndef __BASE_MESSAGE_LAYER_H__
#define __BASE_MESSAGE_LAYER_H__

#include "Common.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

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
	virtual void createMessage();
	virtual void nextPage();                  // 改ページ
    virtual void onAllLetterDisplayed(){};    // ページ内のすべての文字を表示し終えた時
    virtual void onAllPageDisplayed();        // すべてのページを表示し終えた時
    virtual void close();                     // メッセージウインドウを閉じる
	
	// インスタンス変数
private:
    EventListenerKeyboardLayer* listenerKeyboard { nullptr };
	float span { 0.05f };
	vector<Action*> letterActions {};
	function<void()> callback { nullptr };
protected:
	Sprite* frame { nullptr };
	Label* message { nullptr };
	queue<string> pages {};
	string fontPath {};
	int fontSize { 24 };
	TextVAlignment v_alignment { TextVAlignment::TOP };
	TextHAlignment h_alignment { TextHAlignment::LEFT };
    bool _isAllLetterDisplayed { false };
    bool _isAllPageDisplayed { false };
};

#endif // __BASE_MESSAGE_LAYER_H__
