//
//  TitleScene.h
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "Scenes/baseScene.h"

class TitleMainMenuLayer;
class SaveDataSelector;

class TitleScene : public baseScene
{
	// 列挙型
	enum struct MenuType
	{
		BEGINING,
		FINISH,
		SIZE,
	};
	// クラスメソッド
public:
	static Scene* createScene();
	CREATE_FUNC(TitleScene);
	
	// インスタンスメソッド
private:
	virtual bool init();
	void onPreloadFinished();
	void onStartSelected();
	void onContinueSelected();
	void onExitSelected();
	void onSaveDataSelected(PlayerDataManager::SaveIndex saveIdx);
public:
	TitleScene();
	~TitleScene();
	
	// インスタンス変数
	TitleMainMenuLayer* mainMenu { nullptr };
	SaveDataSelector* saveDataSelector { nullptr };
};

#endif // __TITLE_SCENE_H__