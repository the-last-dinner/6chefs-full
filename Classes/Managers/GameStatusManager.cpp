#include "GameStatusManager.h"

// 唯一のインスタンスを初期化
static GameStatusManager * _instance = nullptr;

// インスタンスの生成&取得
GameStatusManager * GameStatusManager::getInstance()
{
	if (!_instance) _instance = new GameStatusManager();
	return _instance;
}

// インスタンスの破棄
void GameStatusManager::destroy()
{
	delete _instance;
	return;
}

// コンストラクタ
GameStatusManager::GameStatusManager():
currentStatus(Status::TITLE),
formerStatus(Status::TITLE),
time(0.f)
{FUNCLOG}

// デストラクタ
GameStatusManager::~GameStatusManager()
{FUNCLOG}

void GameStatusManager::setCurrentGameStatus(Status status, float second)
{
	FUNCLOG
	this->formerStatus = this->currentStatus;
	this->currentStatus = status;
	if (second != 0){
		this->time = second;
	}
	return;
}

GameStatusManager::Status GameStatusManager::getCurrentGameState()
{
	FUNCLOG
	return this->currentStatus;
}

void GameStatusManager::updateGameStatus(float delta)
{
	FUNCLOG
	switch (this->currentStatus)
	{
		case Status::WAIT:
			if (this->time > 0){
				this->time -= delta;
				if (this->time <= 0){
					this->currentStatus = this->formerStatus;
					this->time = 0;
				}
			}
			break;
        default:
            break;
	}
}