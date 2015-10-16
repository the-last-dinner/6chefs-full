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

// インスタンスメソッド
public:
protected:
    MovePattern();
    ~MovePattern();
    virtual bool init(Character* chara);
    virtual void move() = 0;
    
};

#endif /* defined(__LastSupper__MovePattern__) */
