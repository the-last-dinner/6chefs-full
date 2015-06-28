//
//  PlayerDataManager.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/06/28.
//
//

#ifndef __LastSupper__PlayerDataManager__
#define __LastSupper__PlayerDataManager__

#include "define.h"

class PlayerDataManager
{
//singleton用関数
public:
    static PlayerDataManager* getInstance();
    static void  destroy();
private:
    PlayerDataManager();    //コンストラクタ
    ~PlayerDataManager();   //デストラクタ
    PlayerDataManager(const PlayerDataManager& other){};              //コピーコンストラクタ
    PlayerDataManager& operator = (const PlayerDataManager& other); //代入演算子
    
//
};

#endif /* defined(__LastSupper__PlayerDataManager__) */
