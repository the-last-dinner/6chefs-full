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

class Character : public Node
{
	// 列挙型
public:
	enum struct CharacterType
	{
		MAIN,
		MOB,
		ENEMY,
		SIZE,
	};
	
	enum struct Direction
	{
		FRONT,
		RIGHT,
		LEFT,
		BACK,
		SIZE,
	};
	
	enum struct DataType
	{
		ID,
		TexturePrefix,
		Name,
		SIZE,
	};
	
	// クラスメソッド
public:
	static Character* create(int charaId, CharacterType charaType, Direction direction);
	
	// クラス変数
private:
	static const vector<vector<string>> characterDatas;
	static const string basePath;
	
	// インスタンスメソッド
private:
	Character();
	~Character();
	virtual bool init(int charaId, CharacterType charaType, Direction direction);
public:
	void changeDirection(Direction direction);
	
	// インスタンス変数
private:
	Sprite* character;												// キャラクターのSprite部分
	string texturePrefix;											// キャラプロパティリストファイル名の先頭部分
	CharacterType charaType;
	Direction currentDirection;										// 現在向いている方向
	Animation* pAnimation[static_cast<int>(Direction::SIZE)];		// キャラが動いているときのアニメーション
};

#endif // __CHARACTER_H__
