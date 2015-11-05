//
//  Party.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/05.
//
//

#include "MapObjects/Party.h"

#include "MapObjects/Character.h"

// コンストラクタ
Party::Party() {FUNCLOG};

// デストラクタ
Party::~Party() {FUNCLOG};

// 初期化
bool Party::init(Character* mainCharacter)
{
    if(!mainCharacter) return false;
    
    // 先頭に主人公を配置する
    this->addCharacter(mainCharacter);
    
    return true;
}

// パーティにキャラクタを追加
void Party::addCharacter(Character* character)
{
    this->members.pushBack(character);
}

// パーティを移動
void Party::move(const Point& movementVector, float ratio, function<void()> callback)
{
    Direction direction {Direction::SIZE};
    Point destPos { Point::ZERO };
    Vec2 movement { movementVector };
    
    for(int i { 0 }; i < this->members.size(); i++)
    {
        Character* character {this->members.at(i)};
        
        // 主人公以外について
        if(i != 0)
        {
            character->setDirection(direction);
            movement = destPos - character->getPosition();
        }
        
        if(movement != Vec2::ZERO) character->runAction(character->createWalkByAction(movement));
        
        direction = character->getDirection();
        destPos = character->getPosition();
    }
}

// 主人公を取得
Character* Party::getMainCharacter() const
{
    return this->members.at(0);
}

// パーティメンバーを取得
Vector<Character*> Party::getMembers() const
{
    return this->members;
}
