//
//  DungeonMainMenuLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/09/06.
//
//

#ifndef __LastSupper__DungeonMainMenuLayer__
#define __LastSupper__DungeonMainMenuLayer__

#include "Layers/Menu/MenuLayer.h"

class DungeonMainMenuLayer : public MenuLayer
{
	// 列挙型
public:
	enum struct Type
	{
		ITEM,
		SAVE,
		CHARA,
		TITLE,
		CLOSE,
		SIZE
	};
	
	// クラスメソッド
public:
	CREATE_FUNC(DungeonMainMenuLayer)
    virtual void show();
    void show2();
    virtual void hide();
	// インスタンスメソッド
private:
	DungeonMainMenuLayer();
	~DungeonMainMenuLayer();
	virtual bool init();

	virtual void onIndexChanged(int newIdx, bool sound = true);
	virtual void onSpacePressed(int idx);
	virtual void onMenuKeyPressed();
};

#endif /* defined(__LastSupper__DungeonMainMenuLayer__) */
