//
//  JsonUtils.cpp
//  LastSupper
//
//  Created by Ryoya Ino on 2015/12/04.
//
//

#include "Utils/JsonUtils.h"

// JSONファイルの読み込み
rapidjson::Document LastSupper::JsonUtils::readJsonFile(const string& path)
{
    const char* cpath = path.c_str();
    rapidjson::Document doc {nullptr};
    FILE* fp;
    char buf[512];
    
    // ファイル操作
    fp = fopen(cpath, "rb");
    FileReadStream rs(fp, buf, sizeof(buf));
    doc.ParseStream(rs);
    fclose(fp);
    
    //構文エラー判定
    bool error = doc.HasParseError();
    if(error){
        size_t offset = doc.GetErrorOffset();
        ParseErrorCode code = doc.GetParseError();
        const char* msg = GetParseError_En(code);
        CCLOG("GlobalTemplate JSON Parse Error : %d:%d(%s)\n", static_cast<int>(offset), code, msg);
        return nullptr;
    }
    
    return doc;
}

// JSONファイルの書き出し
void LastSupper::JsonUtils::writeJsonFile(const string& path, const rapidjson::Document& doc)
{
    const char* cpath = path.c_str();
    FILE* fp;
    char buf[512];
    
    fp = fopen(cpath, "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));
    Writer<FileWriteStream> writerf(ws);
    doc.Accept(writerf);
    fclose(fp);
    
    return;
}