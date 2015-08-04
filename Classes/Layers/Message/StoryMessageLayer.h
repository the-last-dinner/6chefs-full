//
//  StoryMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/08/02.
//
//

#ifndef __STORY_MESSAGE_LAYER_H__
#define __STORY_MESSAGE_LAYER_H__

#include "Layers/Message/baseMessageLayer.h"

class StoryMessageLayer : public baseMessageLayer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(StoryMessageLayer, queue<string>);
	
	// インスタンスメソッド
private:
	StoryMessageLayer();
	~StoryMessageLayer();
	virtual bool init(const queue<string> pages);
};

#endif // __STORY_MESSAGE_LAYER_H__
