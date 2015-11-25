//
//  EnemyData.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#ifndef LastSupper_EnemyData_h
#define LastSupper_EnemyData_h

#include "define.h"
#include "Datas/MapObject/CharacterData.h"

struct EnemyData
{
    int enemy_id { static_cast<int>(EnemyID::UNDIFINED) };
    int to_map_id {static_cast<int>(MapID::UNDIFINED)};
    int to_x { 0 };
    int to_y { 0 };
    int change_map_counter { -1 };
    float summon_delay { 0.f };
    float speed_ratio { 1.0f };
    EnemyMovePattern move_pattern {EnemyMovePattern::SIZE};
    CharacterData chara_data {};
};

#endif
