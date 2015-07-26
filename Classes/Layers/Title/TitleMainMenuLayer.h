//
//  TitleMainMenuLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#ifndef __TITLE_MAIN_MENU_LAYER_H__
#define __TITLE_MAIN_MENU_LAYER_H__

#include "Common.h"
#include "Layers/baseMenuLayer.h"
#include "Scenes/DungeonScene.h"

class TitleMainMenuLayer : public baseMenuLayer
{
	// 列挙型、構造他
public:
	enum struct MenuType
	{
		START,
		CONTINUE,
		FINISH,
	};
	
	// クラスメソッド
public:
	CREATE_FUNC(TitleMainMenuLayer);
	
	// クラス変数
private:
	static const map<string, MenuType> menu;
	
	// インスタンスメソッド
private:
	TitleMainMenuLayer();
	~TitleMainMenuLayer();
	virtual bool init();
	void moveCursor(bool sound);
	void onSpacePressed();
};

#endif // __TITLE_MAIN_MENU_LAYER_H__
