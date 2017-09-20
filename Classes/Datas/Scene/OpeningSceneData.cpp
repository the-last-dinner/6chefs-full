//
//  OpeningSceneData.cpp
//  6chefs2
//
//  Created by Ryoya Ino on 2017/02/13.
//
//

#include "Datas/Scene/OpeningSceneData.h"
#include "Managers/ResourcesManager.h"

bool OpeningSceneData::init()
{
    FUNCLOG
    
    this->textureFilePaths = {};
    this->soundFilePaths = {};
    
    return true;
}
