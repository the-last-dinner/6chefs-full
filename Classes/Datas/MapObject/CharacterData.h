//
//  CharacterData.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/18.
//
//

#ifndef CharacterData_h
#define CharacterData_h

#include "define.h"

struct CharacterData
{
    int chara_id {static_cast<int>(CharacterID::UNDIFINED)};
    int obj_id {static_cast<int>(ObjectID::UNDIFINED)};
    Location location {};
    CharacterMovePattern move_pattern {CharacterMovePattern::NONE};
    CharacterData(){};
    CharacterData(const int chara_id, const int obj_id, const Location& location):chara_id(chara_id), obj_id(obj_id), location(location){};
};

#endif /* CharacterData_h */
