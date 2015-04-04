#include "model/BaseTitleMenu.h"

BaseTitleMenu::BaseTitleMenu()
{
	this->init();
}

BaseTitleMenu::~BaseTitleMenu()
{

}

void BaseTitleMenu::init()
{
	for (int i = 0; i < this->mainMenuString.size(); i++)
	{
		this->mainMenu.insert(map<int, string>::value_type(i, this->mainMenuString.at(i)));
	}
	this->mainCursorPosition = 0;
}