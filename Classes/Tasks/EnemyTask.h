//
//  EnemyTask.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/21.
//
//

#ifndef EnemyTask_h
#define EnemyTask_h

#include "Tasks/GameTask.h"

class EnemyTask : public GameTask
{
// クラスメソッド
public:
    CREATE_FUNC(EnemyTask);

// インスタンスメソッド
private:
    EnemyTask();
    ~EnemyTask();
    bool init();
};

#endif /* EnemyTask_h */
