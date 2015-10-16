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
public:
    static const float DURATION_FOR_ONE_STEP;

// クラスメソッド
public:
	static Character* create(int charaId, const Direction direction);
    
// インスタンス変数
private:
    Sprite* character { nullptr };												// キャラクターのSprite部分
    string texturePrefix {};											// キャラプロパティリストファイル名の先頭部分
    Direction direction {Direction::SIZE};											// 現在向いている方向
    bool _isMoving { false };
    bool stampingRightFoot { false };
	
// インスタンスメソッド
private:
	Character();
	~Character();
	virtual bool init(int charaId, const Direction direction);
public:
	void setDirection(Direction direction);
	Direction getDirection();
	void setMoving(bool _isMoving);
	bool isMoving();
    void stamp(const Direction direction, float ratio = 1.0f);
    ActionInterval* createWalkByAction(const Point& vector, float ratio = 1.0f);
    ActionInterval* createWalkByAction(const Direction direction, float ratio = 1.0f);
    ActionInterval* createWalkByAction(const Direction direction[2], float ratio = 1.0f);
};

#endif // __CHARACTER_H__
