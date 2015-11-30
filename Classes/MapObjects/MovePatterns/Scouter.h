//
//  Scouter.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#ifndef Scouter_h
#define Scouter_h

#include "MapObjects/MovePatterns/MovePattern.h"

class Scouter : public MovePattern
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Scouter, Character*)

// インスタンスメソッド
private:
    Scouter();
    ~Scouter();
    virtual bool init(Character* character) override;
};

#endif /* Scouter_h */
