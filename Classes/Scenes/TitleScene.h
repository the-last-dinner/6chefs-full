#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "Scenes/baseScene.h"
#include "Datas/Scene/TitleSceneData.h"
#include "Layers/Title/TitleMainMenuLayer.h"

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
public:
	TitleScene();
	~TitleScene();
private:
	virtual bool init();
	void loadFinished();
	
	// インスタンス変数
private:
	TitleSceneData* data;
};

#endif // __TITLE_SCENE_H__