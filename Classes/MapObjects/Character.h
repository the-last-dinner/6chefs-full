//
//  Character.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/06/15.
//
//

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "MapObjects/MapObject.h"

struct CharacterData;

class Character : public MapObject
{
// 定数
private:
    static const string basePath;

// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(Character, const CharacterData&);
    
// インスタンス変数
private:
    int charaId { static_cast<int>(CharacterID::UNDIFINED) };                   // キャラクタID
    Sprite* character { nullptr };												// キャラクターのSprite部分
    string texturePrefix {};                                                    // キャラプロパティリストファイル名の先頭部分
    Direction direction {Direction::SIZE};										// 現在向いている方向
    bool stampingRightFoot { false };
	
// インスタンスメソッド
public:
	Character();
	~Character();
    bool init(const CharacterData& data);
    
    int getCharacterId() const;
    Direction getDirection() const;
    
	void setDirection(Direction direction);
	void setMoving(bool _isMoving);
    void stamp(const Direction direction, const int gridNum , const float ratio = 1.0f);
    bool walkBy(const Direction& direction, function<void()> onWalked, const float ratio = 1.0f, const bool back = false);
    bool walkBy(const vector<Direction>& directions, function<void()> onWalked, const float ratio = 1.0f, const bool back = false);
    void walkBy(const Direction& direction, const int gridNum, function<void(bool)> callback, const float ratio = 1.0f, const bool back = false);
    void walkBy(const vector<Direction>& directions, const int gridNum, function<void(bool)> callback, const float ratio = 1.0f, const bool back = false);
    void walkByQueue(deque<Direction> directionsQueue, function<void(bool)> callback, const float ratio = 1.0f, const bool back = false);
    void walkByQueue(deque<vector<Direction>> directionsQueue, function<void(bool)> callback, const float ratio = 1.0f, const bool back = false);
};

#endif // __CHARACTER_H__
