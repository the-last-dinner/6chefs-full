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
class LoadingLayer;
class SceneData;

class baseScene : public Scene
{
// インスタンスメソッド
private:
	virtual void onPreloadFinished(LoadingLayer* loadingLayer) = 0;
protected:
	baseScene();
	~baseScene();
	bool init(SceneData* data);
    virtual void onEnter() override;
	
// インスタンス変数
protected:
	SceneData* data { nullptr };
};

#endif // __BASE_SCENE_H__
