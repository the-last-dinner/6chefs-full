//
//  SystemMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __SYSTEM_MESSAGE_LAYER_H__
#define __SYSTEM_MESSAGE_LAYER_H__

#include "Layers/baseMessageLayer.h"

class SystemMessageLayer : public baseMessageLayer
{
	// クラスメソッド
public:
	static SystemMessageLayer* createWithPages(const queue<string>& pages);
	
	// インスタンスメソッド
private:
	SystemMessageLayer();
	~SystemMessageLayer();
	virtual bool init(const queue<string>& pages);
};

#endif // __SYSTEM_MESSAGE_LAYER_H__
