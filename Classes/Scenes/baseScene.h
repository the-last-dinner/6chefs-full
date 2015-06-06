//
//  baseScene.h
//  LastSupper
//
//  Created by Kohei on 2015/06/05.
//
//

#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "Common.h"

class baseScene : public Layer
{
	// インスタンスメソッド
public:
	baseScene();
	~baseScene();
};

// セーブデータのロード時に呼び出すcreate関数
// セーブデータを渡す
#define CREATE_FUNC_WITH_MAP(__TYPE__) \
static __TYPE__* create(const SaveData& saveData) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(saveData)) { \
pRet->autorelease(); \
return pRet; \
} \
else { \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

// ロードを挟んで表示したいシーンのenumを引数にとるcreate関数の宣言
// 引数はinitに引き渡される
#define CREATE_FUNC_WITH_SCENE_TYPE(__TYPE__) \
static __TYPE__* create(const SceneType& sceneType) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(sceneType)) { \
pRet->autorelease(); \
return pRet; \
} \
else { \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}

#endif // __BASE_SCENE_H__
