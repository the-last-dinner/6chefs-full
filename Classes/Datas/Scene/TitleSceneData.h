//
//  TitleSceneData.h
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#ifndef __TITLE_SCENE_DATA_H__
#define __TITLE_SCENE_DATA_H__

#include "Common.h"
#include "SceneData.h"

class TitleSceneData : public SceneData
{
	// インスタンスメソッド
public:
	TitleSceneData();
private:
	~TitleSceneData();
	void init();
};

#endif // __TITLE_SCENE_DATA_H__