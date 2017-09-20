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
