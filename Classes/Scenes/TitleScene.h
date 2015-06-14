#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "baseScene.h"
#include "LoadScene.h"

class TitleScene : public baseScene
{
	// 列挙型
	enum struct MenuType
	{
		BEGINING,
		FINISH,
		SIZE,
	};
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(TitleScene);
	
	// クラス変数
	static const vector<string> menuStrings;
	
	// インスタンスメソッド
public:
	TitleScene();
	~TitleScene();
private:
	virtual bool init();
	virtual void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	void pressSpaceKey();
	void moveCursor();
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener;
	int menuCounter;
};

#endif // __TITLE_SCENE_H__