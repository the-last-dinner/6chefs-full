#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "define.h"
class GameStatusManager{
	public:
		void setCurrentGameState(GameState status, float second = 0);
		GameState getCurrentGameState();
		static GameStatusManager * getInstance();
		void updateGameState(float delta);

	private:
		GameStatusManager();
		~GameStatusManager();
		void init();
		GameState currentState;
		GameState formerState;
		float time;
	};

#endif //_GAME_STATE_H_