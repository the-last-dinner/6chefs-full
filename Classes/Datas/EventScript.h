//
//  EventScript.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#ifndef __LastSupper__EventScript__
#define __LastSupper__EventScript__

#include <stdio.h>
#include "cocos2d.h"
#include <iostream>
#include <fstream>

class EventScript
{
public:
    EventScript();
    ~EventScript();
    void readScript();
    std::string trim(const std::string& string, const char* trimCharacterList);
private:
    cocos2d::FileUtils * fu;
};
#endif /* defined(__LastSupper__EventScript__) */
