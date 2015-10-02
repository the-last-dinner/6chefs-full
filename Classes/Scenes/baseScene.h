//
//  baseScene.h
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "Common.h"

class EventListenerKeyboardLayer;
class SceneData;

class baseScene : public Layer
{
	// インスタンスメソッド
private:
	virtual void onPreloadFinished() = 0;
	virtual void onCursorKeyPressed(const Key& key){};
	virtual void onSpaceKeyPressed(){};
	virtual void onMenuKeyPressed(){};
	virtual void onDashKeyPressed(){};
protected:
	baseScene();
	~baseScene();
	bool init(SceneData* data);
	
	// インスタンス変数
protected:
	SceneData* data { nullptr };
    EventListenerKeyboardLayer* listener { nullptr };
};

#endif // __BASE_SCENE_H__
