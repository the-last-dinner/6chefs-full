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
Party::~Party()
{
    FUNCLOG

    this->members.clear();
};

// 初期化
bool Party::init(const vector<CharacterData>& datas)
{
    if(datas.empty()) return false;
    
    // データを元にキャラクタを生成して格納
    for(CharacterData data : datas)
    {
        this->members.pushBack(Character::create(data));
    }
    
    return true;
}

// パーティにキャラクタを追加
void Party::addMember(Character* character)
{
    character->setHit(false);
    this->members.pushBack(character);
}

// パーティを移動
bool Party::move(const vector<Direction>& directions, float ratio, function<void()> callback)
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
            cb = [this, callback, character]
            {
                callback();
                if(this->onPartyMoved) this->onPartyMoved(character->getGridRect());
            };
        }
        // 主人公以外について
        if(i != 0)
        {
            character->setDirection(direction);
            dirs = MapUtils::vecToDirections(destPos - character->getPosition());
        }
        
        if(!character->walkBy(dirs, cb, ratio)) return false;
        
        direction = character->getDirection();
        destPos = character->getPosition();
    }
    
    return true;
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

// パーティのキャラクターデータの取得
vector<CharacterData> Party::getMembersData() const
{
    vector<CharacterData> datas {};
    int member_count = this->members.size();
    for (int i = 0; i < member_count; i++)
    {
        datas.push_back(this->members.at(i)->getCharacterData());
    }
    return datas;
}
