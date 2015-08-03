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
public:
	// クラスメソッド
public:
	static CharacterMessageLayer* createWithPages(const queue<string>& pages);
	
	// インスタンスメソッド
private:
	CharacterMessageLayer();
	~CharacterMessageLayer();
	virtual bool init(const queue<string>& pages);

	// インスタンス変数
private:
	string charaName;
	string charaImgFilePath;
};

#endif // __CHARACTER_MESSAGE_LAYER_H__
