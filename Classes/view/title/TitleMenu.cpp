#include "TitleMenu.h"

using namespace cocos2d;

bool TitleMenu::init()
{
	if (!Layer::init()){
		return false;
	}
	Size winSize = Director::getInstance()->getWinSize();
	auto bgi = Sprite::create("img/title.png");
	bgi->setPosition(Point(winSize.width / 2.0f, winSize.height / 2.0f));
	this->addChild(bgi);

	auto menu1 = Label::createWithSystemFont("Å‰‚©‚ç", "ƒƒCƒŠƒI", 32);
	menu1->setPosition(Point(winSize.width / 2.0f, winSize.height / 2.0f));
	this->addChild(menu1);
	return true;
}