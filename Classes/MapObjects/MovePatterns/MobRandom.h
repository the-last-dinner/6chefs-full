//
//  MobRandom.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/12/19.
//
//

#ifndef MobRandom_h
#define MobRandom_h

#include "MapObjects/MovePatterns/MovePattern.h"

class MobRandom : public MovePattern
{
// 定数
private:
    static const float WAIT_DURATION;
    static const float WAIT_DURATION_RANDOM_RANGE;
    static const int DISTANCE;
    static const float SPEED_RATIO;
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(MobRandom, Character*)
    
// インスタンス変数
private:
    Point homePosition { Point::ZERO };
    
// インスタンスメソッド
private:
    MobRandom();
    ~MobRandom();
    virtual bool init(Character* chara);
    virtual void start();
    void move();
    void scheduleMove();
};

#endif /* MobRandom_h */
