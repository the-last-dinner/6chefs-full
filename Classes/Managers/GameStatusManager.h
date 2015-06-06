#ifndef __GAME_STATUS_MANAGER_H__
#define __GAME_STATUS_MANAGER_H__

#include "define.h"

class GameStatusManager{
	// 構造体、列挙型
public:
	enum struct Status
	{
		WAIT,
		TITLE,
		LOAD,
	};
	
	// クラスメソッド
public:
	static GameStatusManager * getInstance();
	static void destroy();
	
	// インスタンスメソッド
private:
	GameStatusManager();												// コンストラクタ
	GameStatusManager(const GameStatusManager& other);					// コピーコンストラクタ
	GameStatusManager& operator = (const GameStatusManager& other);		// 代入演算子
public:
	~GameStatusManager();												// デストラクタ
	void setCurrentGameStatus(Status status, float second = 0);
	Status getCurrentGameState();
	void updateGameStatus(float delta);

	// インスタンス変数
private:
	Status currentStatus;		// 現在のゲーム状態
	Status formerStatus;		// 前のゲーム状態
	float time;
};

#endif //__GAME_STATUS_MANAGER_H__