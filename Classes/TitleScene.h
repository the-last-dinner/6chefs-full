#include "cocos2d.h"
#include "ActionKey.h"

class TitleScene : public cocos2d::Scene
{
public:
	TitleScene();
	~TitleScene();
	virtual bool init();
	static Scene * createScene();
};