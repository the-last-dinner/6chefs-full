//
//  Enemy.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/18.
//
//

#ifndef __LastSupper__Enemy__
#define __LastSupper__Enemy__

#include "MapObjects/Character.h"

class Enemy : public Character
{
// クラスメソッド
public:

// インスタンス変数
private:
    int enemyId { 0 };
    
// インスタンスメソッド
private:
    Enemy();
    ~Enemy();
    bool init();
public:
    int getEnemyId() const;
    void onEnterMap(const Point& gridPosistion);
    void onPartyMoved(const Point& gridPosition);
};

#endif /* defined(__LastSupper__Enemy__) */
