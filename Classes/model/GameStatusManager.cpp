#include "model/GameStatusManager.h"
#include <iostream>

static GameStatusManager * _instance;

GameStatusManager * GameStatusManager::getInstance()
{
	if (!_instance)
	{
		_instance = new GameStatusManager();
	}
	return _instance;
}

GameStatusManager::GameStatusManager()
{	
	std::cout << "Constructor GameStatusManager called" << std::endl;
	this->init();
}

GameStatusManager::~GameStatusManager()
{
	std::cout << "Destructor GameStatusManager called" << std::endl;
}

void GameStatusManager::init()
{
	this->currentState = GameState::TITLE_MAIN;
}

void GameStatusManager::setCurrentGameState(GameState status, float second)
{	
	std::cout << "set currentGameState" << std::endl;
	this->formerState = this->currentState;
	this->currentState = status;
	if (second != 0){
		this->time = second;
	}
	return;
}

GameState GameStatusManager::getCurrentGameState()
{
	return this->currentState;
}

void GameStatusManager::updateGameState(float delta)
{
	switch (this->currentState)
	{
		case GameState::WAIT:
			if (this->time > 0){
				this->time -= delta;
				if (this->time <= 0){
					this->currentState = this->formerState;
					this->time = 0;
				}
			}
			break;
        default:
            break;
	}
}