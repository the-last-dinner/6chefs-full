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

class Character : public MapObject
{
// 定数
private:
    static const string basePath;

// クラスメソッド
public:
	static Character* create(int charaId, const Direction direction);
    
// インスタンス変数
private:
    int charaId { static_cast<int>(CharacterID::UNDIFINED) };                   // キャラクタID
    Sprite* character { nullptr };												// キャラクターのSprite部分
    string texturePrefix {};                                                    // キャラプロパティリストファイル名の先頭部分
    Direction direction {Direction::SIZE};										// 現在向いている方向
    bool stampingRightFoot { false };
	
// インスタンスメソッド
private:
	Character();
	~Character();
	virtual bool init(int charaId, const Direction direction);
public:
    int getCharacterId() const;
    Direction getDirection() const;
    
	void setDirection(Direction direction);
	void setMoving(bool _isMoving);
    void stamp(const Direction direction, const int gridNum , const float ratio = 1.0f);
    void walkBy(const Direction& direction, const int gridNum, function<void()> onWalked, const float ratio = 1.0f);
    void walkBy(const vector<Direction>& directions, const int gridNum, function<void()> onWalked, const float ratio = 1.0f);
};

#endif // __CHARACTER_H__
