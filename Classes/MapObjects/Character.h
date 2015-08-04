//
//  Character.h
//  LastSupper
//
//  Created by Kohei on 2015/06/15.
//
//

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Common.h"
#include "MapObject.h"

class Character : public MapObject
{
	// クラスメソッド
public:
	static Character* create(int charaId, Direction direction);
	
	// クラス変数
private:
	static const string basePath;
public:
	static const float SECOND_PER_GRID;
	
	// インスタンスメソッド
private:
	Character();
	~Character();
	virtual bool init(int charaId, Direction direction);
public:
	void setDirection(Direction direction);
	Direction getDirection();
	void setMoving(bool _isMoving);
	bool isMoving();
	void stamp(float ratio = 1.0f);
	
	// インスタンス変数
private:
	Sprite* character;												// キャラクターのSprite部分
	string texturePrefix;											// キャラプロパティリストファイル名の先頭部分
	Direction direction;											// 現在向いている方向
	bool _isMoving;
	bool identifier;
};

#endif // __CHARACTER_H__
