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
private:
	virtual void onPreloadFinished() = 0;
	virtual void onCursorKeyPressed(const ActionKeyManager::Key key){};
	virtual void onSpaceKeyPressed(){};
	virtual void onMenuKeyPressed(){};
	virtual void onDashKeyPressed(){};
protected:
	baseScene();
	~baseScene();
	bool init(SceneData* data);
public:
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode);
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
protected:
	SceneData* data { nullptr };
	EventListenerKeyboard* listenerKeyboard { nullptr };
};

#endif // __BASE_SCENE_H__
