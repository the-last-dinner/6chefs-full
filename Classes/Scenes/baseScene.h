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

class SceneData;

class baseScene : public Layer
{
	// インスタンスメソッド
protected:
	baseScene();
	~baseScene();
	bool init(SceneData* data);
	virtual void onPreloadFinished() = 0;
public:
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
protected:
	SceneData* data { nullptr };
};

#endif // __BASE_SCENE_H__
