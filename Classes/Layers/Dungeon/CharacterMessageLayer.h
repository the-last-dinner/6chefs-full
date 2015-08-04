//
//  CharacterMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __CHARACTER_MESSAGE_LAYER_H__
#define __CHARACTER_MESSAGE_LAYER_H__

#include "Layers/baseMessageLayer.h"

class CharacterMessageLayer : public baseMessageLayer
{
	// クラスメソッド
private:
	static CharacterMessageLayer* createWithPages(const queue<string>& pages);
	
public:
	static CharacterMessageLayer* createWithCharaId(const int& charaId, const queue<string>& pages);
	static CharacterMessageLayer* createWithName(const int& charaId, const string& name, const queue<string>& pages);
	static CharacterMessageLayer* createWithName(const string& name, const queue<string>& pages);
	
	// インスタンスメソッド
private:
	CharacterMessageLayer();
	~CharacterMessageLayer();
	virtual bool init();
	void display();
public:
	void setCharacterId(const int& charaId);
	void setCharacterName(const string& name);

	// インスタンス変数
private:
	int charaId;
	string charaName;
};

#endif // __CHARACTER_MESSAGE_LAYER_H__
