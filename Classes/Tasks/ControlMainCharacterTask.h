//
//  ControlMainCharacterTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#ifndef __LastSupper__ControlMainCharacterTask__
#define __LastSupper__ControlMainCharacterTask__

#include "Common.h"

class DungeonScene;

class ControlMainCharacterTask : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(ControlMainCharacterTask, DungeonScene*)

// インスタンス変数
private:
    DungeonScene* scene {nullptr};
    
// インスタンスメソッド
private:
    ControlMainCharacterTask();
    ~ControlMainCharacterTask();
    bool init(DungeonScene* dungeonScene);
public:
    void turn(const Direction& direction);      // 向きを変える
    void search();                              // 目の前を調べる
    void walking(vector<Direction> directions); // 歩行中
};

#endif /* defined(__LastSupper__ControlMainCharacterTask__) */
