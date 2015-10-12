//
//  StringUtils.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/10/12.
//
//

#include "StringUtils.h"

// 文字列を置換する
string LastSupper::StringUtils::strReplace(const string& pattern, const string& replacement, string target)
{
    std::string::size_type Pos(target.find(pattern));
    while( Pos != std::string::npos )
    {
        target.replace( Pos, pattern.length(), replacement);
        Pos = target.find( pattern, Pos + replacement.length() );
    }
    return target;
}

//sprinfでformatした文字列を取得
string LastSupper::StringUtils::getSprintf(const string& format, const string& str){
    char c[100];
    sprintf(c, format.c_str(), str.c_str());
    return string(c);
}