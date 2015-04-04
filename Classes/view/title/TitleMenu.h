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
    TitleMenu();
	CREATE_FUNC(TitleMenu);

private:
<<<<<<< HEAD
	BaseTitleMenu baseTitleMenu;
=======
    cocos2d::FileUtils * fu;
>>>>>>> 8ebd0efd1ba1f794a0b4f6aa08b125d46c7f3170
};

#endif // _TITLE_MENU_H_