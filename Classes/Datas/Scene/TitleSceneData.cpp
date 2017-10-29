//
//  TitleSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#include "Datas/Scene/TitleSceneData.h"
#include "Managers/ResourcesManager.h"

// コンストラクタ
TitleSceneData::TitleSceneData() {FUNCLOG}

// デストラクタ
TitleSceneData::~TitleSceneData() {FUNCLOG}

// 初期化
bool TitleSceneData::init()
{
    FUNCLOG
    
    this->textureFilePaths = {};
    this->soundFilePaths = {};
    
	return true;
}
