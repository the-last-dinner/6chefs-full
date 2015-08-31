//
//  CharacterMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __CHARACTER_MESSAGE_LAYER_H__
#define __CHARACTER_MESSAGE_LAYER_H__

#include "Layers/Message/baseMessageLayer.h"

#include "cocos-ext.h"

class CharacterMessageLayer : public baseMessageLayer
{
	// クラスメソッド
private:
	CREATE_FUNC_WITH_PARAM(CharacterMessageLayer, queue<string>);
public:
	static CharacterMessageLayer* createWithCharaId(const int& charaId, const int& imgDiffId, const queue<string>& pages);
	static CharacterMessageLayer* createWithName(const int& charaId, const int& imgDiffId, const string& name, const queue<string>& pages);
	static CharacterMessageLayer* createWithName(const string& name, const queue<string>& pages);
	
	// クラス変数
private:
	static constexpr float TOP_MARGIN {50};
	static constexpr float LEFT_MARGIN {60};
	static constexpr float H_MARGIN_S {30};
	
	// インスタンスメソッド
private:
	CharacterMessageLayer();
	~CharacterMessageLayer();
	virtual bool init(const queue<string>& pages);
	virtual void createMessage();
public:
	void setCharacterId(const int& charaId);
	void setImgDiffId(const int& imgDiffId);
	void setCharacterName(const string& name);

	// インスタンス変数
private:
	int charaId { -1 };
	int imgDiffId { 0 };
	string charaName { "" };
	ui::Scale9Sprite* nameFrame { nullptr };
};

#endif // __CHARACTER_MESSAGE_LAYER_H__
