//
//  MovePattern.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/16.
//
//

#ifndef __LastSupper__MovePattern__
#define __LastSupper__MovePattern__

#include "Common.h"

class Character;

class MovePattern : public Ref
{
// インスタンス変数
protected:
    Character* chara { nullptr };
    Rect mainCharacterRect { Rect::ZERO };

// インスタンスメソッド
public:
    virtual void start() {};
    virtual void start(const Rect& gridRect);
    virtual void onPartyMoved(const Rect& gridRect);
    virtual bool canGoToNextMap() const { return false; };
    virtual float calcSummonDelay() const { return 0.0f; };
protected:
    MovePattern();
    ~MovePattern();
    virtual bool init(Character* chara);
};

#endif /* defined(__LastSupper__MovePattern__) */
