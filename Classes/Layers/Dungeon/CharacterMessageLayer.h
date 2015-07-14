//
//  CharacterMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __CHARACTER_MESSAGE_LAYER_H__
#define __CHARACTER_MESSAGE_LAYER_H__

#include "Common.h"
#include "Layers/baseMessageLayer.h"

class CharacterMessageLayer : public baseMessageLayer
{
	// クラスメソッド
public:
	CREATE_FUNC(CharacterMessageLayer);
	// インスタンスメソッド
private:
	CharacterMessageLayer();
	~CharacterMessageLayer();
	virtual bool init();
public:
	//virtual void displayMessage(const string& str);
};

#endif // __CHARACTER_MESSAGE_LAYER_H__
