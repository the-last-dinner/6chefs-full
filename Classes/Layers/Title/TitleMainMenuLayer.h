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
	// クラスメソッド
public:
	CREATE_FUNC(TitleMainMenuLayer);
	
	// インスタンスメソッド
private:
	TitleMainMenuLayer();
	~TitleMainMenuLayer();
	virtual bool init();
	void moveCursor(bool sound);
	void onSpacePressed();
};

#endif // __TITLE_MAIN_MENU_LAYER_H__
