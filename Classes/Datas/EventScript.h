//
//  EventScript.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#ifndef __LastSupper__EventScript__
#define __LastSupper__EventScript__

#include "Common.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

class EventScript
{
public:
    enum struct EventType
    {
        PlaySE,
        Fade,
        Move,
        Talk,
        Control,
        Message,
        ChangeMap,
        Read,
        Delay,
        //指示系
        SameTime,
        If,
        Sequence,
    };
    EventScript();
    ~EventScript();
    void readScript();
    void jsonToMap(string json);
    std::string trim(const std::string& string, const char* trimCharacterList);
private:
    cocos2d::FileUtils * fu;
};
#endif /* defined(__LastSupper__EventScript__) */
