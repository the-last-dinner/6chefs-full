//
//  TitleSelectSceneData.cpp
//  6chefs
//
//  Created by Kohei Asami on 2017/09/04.
//
//

#include "Datas/Scene/TitleSelectSceneData.h"

// コンストラクタ
TitleSelectSceneData::TitleSelectSceneData() { FUNCLOG }

// デストラクタ
TitleSelectSceneData::~TitleSelectSceneData() { FUNCLOG }

// 初期化
bool TitleSelectSceneData::init()
{
    this->textureFilePaths =
    {
        "common/img/title_select"
    };
    this->soundFilePaths = {};
    return true;
}
