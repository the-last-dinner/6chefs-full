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
	virtual bool init();
private:
	virtual void update(float delta);
};