#include "cocos2d.h"
#include "ActionKey.h"

class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();
	virtual bool init();
	CREATE_FUNC(TitleScene);
private:
	virtual void update(float delta);
	ActionKey * actionKey;
};