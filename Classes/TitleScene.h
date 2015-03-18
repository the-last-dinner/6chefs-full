#include "cocos2d.h"
#include "Common.h"
#include "view/title/TitleMenu.h"

class TitleScene : public cocos2d::Layer
{
public:
	TitleScene();
	~TitleScene();
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(TitleScene);
private:
	virtual void update(float delta);
	ActionKey * actionKey;
	GameStatusManager * gsManager;
};