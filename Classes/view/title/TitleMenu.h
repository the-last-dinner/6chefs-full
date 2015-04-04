//
//  TitleMenu.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//
#ifndef  _TITLE_MENU_H_
#define _TITLE_MENU_H_
#include "cocos2d.h"
#include "Common.h"
#include "model/BaseTitleMenu.h"

class TitleMenu : public cocos2d::Layer
{
public:
	bool init();
	CREATE_FUNC(TitleMenu);

private:
	BaseTitleMenu baseTitleMenu;
};

#endif // _TITLE_MENU_H_