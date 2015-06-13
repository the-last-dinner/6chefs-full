#include "baseScene.h"

class TitleScene : public baseScene
{
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(TitleScene);
	
	// インスタンスメソッド
public:
	TitleScene();
	~TitleScene();
private:
	virtual bool init();
	virtual void update(float delta);
	void onKeyPressed(EventKeyboard::KeyCode keyCode);
	void onKeyReleased(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
private:
	EventListenerKeyboard* eventListener;
};