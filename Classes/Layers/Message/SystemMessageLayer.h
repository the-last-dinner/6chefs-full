//
//  SystemMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __SYSTEM_MESSAGE_LAYER_H__
#define __SYSTEM_MESSAGE_LAYER_H__

#include "Layers/Message/baseMessageLayer.h"

class SystemMessageLayer : public baseMessageLayer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(SystemMessageLayer, queue<string>);
	
	// インスタンスメソッド
private:
	SystemMessageLayer();
	~SystemMessageLayer();
	virtual bool init(const queue<string>& pages);
};

#endif // __SYSTEM_MESSAGE_LAYER_H__
