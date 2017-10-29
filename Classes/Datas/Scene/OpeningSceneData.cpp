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
    
    string basePath;
    string jsonPath = ResourcesManager::getInstance()->getCurrentFilePath(Resource::ConfigFiles::PRELOAD_LIST);
    int length;
    const rapidjson::Document json = LastSupper::JsonUtils::readJsonCrypted(jsonPath);
    for (rapidjson::Value::ConstMemberIterator itr = json.MemberBegin(); itr != json.MemberEnd(); itr++)
    {
        basePath = ResourcesManager::getInstance()->getCurrentPath() + "/";
        basePath += itr->name.GetString();
        basePath += "/";
        length = itr->value.Size();
        for (int i = 0; i < length; i++)
        {
            this->textureFilePaths.push_back(basePath + itr->value[i].GetString());
        }
    }
    this->soundFilePaths = {};
    
    return true;
}
