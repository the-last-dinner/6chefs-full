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
    virtual void start(const Rect& gridRect) override;
    virtual bool canGoToNextMap() const override;
    virtual float calcSummonDelay() const override;
};

#endif /* Chaser_h */
