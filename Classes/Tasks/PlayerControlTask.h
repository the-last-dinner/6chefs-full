//
//  PlayerControlTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/30.
//
//

#ifndef __LastSupper__ControlMainCharacterTask__
#define __LastSupper__ControlMainCharacterTask__

#include "Tasks/GameTask.h"

class TaskMediator;

class PlayerControlTask : public GameTask
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(PlayerControlTask, TaskMediator*)

// インスタンス変数
private:
    int riddenEventID { static_cast<int>(EventID::UNDIFINED)};
    
// インスタンスメソッド
private:
    PlayerControlTask();
    ~PlayerControlTask();
    bool init(TaskMediator* mediator);
public:
    void turn(const Direction& direction);      // 向きを変える
    void search();                              // 目の前を調べる
    void walking(vector<Direction> directions); // 歩行中
    void onCharacterWalkedOneGrid();            // 一マス分移動し終えた時
};

#endif /* defined(__LastSupper__ControlMainCharacterTask__) */
