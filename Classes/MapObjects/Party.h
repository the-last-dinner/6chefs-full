//
//  Party.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/05.
//
//

#ifndef __LastSupper__Party__
#define __LastSupper__Party__

#include "Common.h"

class Character;

class Party : public Ref
{
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Party, Character*)

// インスタンス変数
private:
    Vector<Character*> members {};

// インスタンスメソッド
private:
    Party();
    ~Party();
    bool init(Character* mainCharacter);
    
public:
    void addMember(Character* character);
    void move(const vector<Direction>& directions, float ratio, function<void()> callback);
    Character* getMainCharacter() const;
    Vector<Character*> getMembers() const;
};

#endif /* defined(__LastSupper__Party__) */
