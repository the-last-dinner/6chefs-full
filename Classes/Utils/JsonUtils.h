//
//  JsonUtils.hpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/04.
//
//

#ifndef JsonUtils_h
#define JsonUtils_h

#include "define.h"
namespace LastSupper
{
    namespace JsonUtils
    {
        rapidjson::Document readJsonFile(const string& path);
        void writeJsonFile(const string& path, const rapidjson::Document& doc);
    }
}

#endif /* JsonUtils_hpp */
