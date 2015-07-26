//
//  LoadingLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#ifndef __LOADING_LAYER_H__
#define __LOADING_LAYER_H__

#include "Common.h"

class LoadingLayer : public Layer
{
	// クラスメソッド
public:
	CREATE_FUNC(LoadingLayer);
	
	// インスタンスメソッド
private:
	LoadingLayer();
	~LoadingLayer();
	virtual bool init();
public:
	void loadFinished(const function<void()>& callback);
};

#endif // __LOADING_LAYER_H__