//
//  StringUtils.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/10/12.
//
//

#ifndef __LastSupper__StringUtils__
#define __LastSupper__StringUtils__

#include "define.h"

namespace LastSupper
{
    namespace StringUtils
    {
        string strReplace(const string& pattern, const string& replacement, string target);
        string getSprintf(const string& format, const string& str);
    }
}

#endif /* defined(__LastSupper__StringUtils__) */
