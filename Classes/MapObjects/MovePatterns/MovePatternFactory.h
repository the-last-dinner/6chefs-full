//
//  MovePatternFactory.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/20.
//
//

#ifndef MovePatternFactory_h
#define MovePatternFactory_h

#include "Common.h"

class MovePattern;

class MovePatternFactory : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC(MovePatternFactory);
    
// インスタンスメソッド
private:
    MovePatternFactory();
    ~MovePatternFactory();
    bool init();
    MovePattern* createMovePattern(const EnemyMovePattern type);
    MovePattern* createMovePattern(const CharacterMovePattern type);
};

#endif /* MovePatternFactory_h */
