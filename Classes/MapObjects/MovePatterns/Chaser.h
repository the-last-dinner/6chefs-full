//
//  Chaser.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#ifndef Chaser_h
#define Chaser_h

#include "MapObjects/MovePatterns/MovePattern.h"

class Chaser : public MovePattern
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Chaser, Character*)

// インスタンスメソッド
private:
    Chaser();
    ~Chaser();
    virtual bool init(Character* character) override;
    virtual bool canGoToNextMap() const override { return true; };
};

#endif /* Chaser_h */
