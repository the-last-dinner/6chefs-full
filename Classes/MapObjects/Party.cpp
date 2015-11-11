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
    this->addMember(mainCharacter);
    
    return true;
}

// パーティにキャラクタを追加
void Party::addMember(Character* character)
{
    character->setHit(false);
    this->members.pushBack(character);
}

// パーティを移動
void Party::move(const vector<Direction>& directions, float ratio, function<void()> callback)
{
    Direction direction {Direction::SIZE};
    Point destPos { Point::ZERO };
    
    for(int i { 0 }; i < this->members.size(); i++)
    {
        Character* character {this->members.at(i)};
        vector<Direction> dirs {};
        function<void()> cb { nullptr };
        
        // 主人公について
        if(i == 0)
        {
            dirs = directions;
            cb = callback;
        }
        // 主人公以外について
        if(i != 0)
        {
            character->setDirection(direction);
            dirs = MapUtils::vecToDirection(destPos - character->getPosition());
        }
        
        character->walkBy(dirs, 1, cb, ratio);
        
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

// リロード
void Party::reload()
{
    Vector<Character*> newMembers {};
    
    for(Character* chara : this->members)
    {
        newMembers.pushBack(Character::create(chara->getCharacterId(), chara->getDirection()));
    }
    
    this->members.clear();
    
    this->members = newMembers;
}