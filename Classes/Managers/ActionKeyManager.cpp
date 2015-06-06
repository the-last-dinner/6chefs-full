#include "ActionKeyManager.h"

// キー変換用マップ
const map<EventKeyboard::KeyCode, ActionKeyManager::Key> ActionKeyManager::keyMap =
{
	{EventKeyboard::KeyCode::KEY_UP_ARROW, ActionKeyManager::Key::UP},
	{EventKeyboard::KeyCode::KEY_W, ActionKeyManager::Key::UP},
	{EventKeyboard::KeyCode::KEY_DOWN_ARROW, ActionKeyManager::Key::DOWN},
	{EventKeyboard::KeyCode::KEY_S, ActionKeyManager::Key::DOWN},
	{EventKeyboard::KeyCode::KEY_LEFT_ARROW, ActionKeyManager::Key::LEFT},
	{EventKeyboard::KeyCode::KEY_A, ActionKeyManager::Key::LEFT},
	{EventKeyboard::KeyCode::KEY_RIGHT_ARROW, ActionKeyManager::Key::RIGHT},
	{EventKeyboard::KeyCode::KEY_D, ActionKeyManager::Key::RIGHT},
	{EventKeyboard::KeyCode::KEY_X, ActionKeyManager::Key::MENU},
	{EventKeyboard::KeyCode::KEY_UNDERSCORE, ActionKeyManager::Key::MENU},
	{EventKeyboard::KeyCode::KEY_SHIFT, ActionKeyManager::Key::DASH},
	{EventKeyboard::KeyCode::KEY_SPACE, ActionKeyManager::Key::SPACE},
};

// 唯一のインスタンスを初期化
static ActionKeyManager* _instance = nullptr;

// インスタンスを生成＆取得
ActionKeyManager* ActionKeyManager::getInstance()
{
	if(!_instance) _instance = new ActionKeyManager();
	return _instance;
}

// インスタンスの破棄
void ActionKeyManager::destroy()
{
	delete _instance;
}

// コンストラクタ
ActionKeyManager::ActionKeyManager()
{FUNCLOG}

// デストラクタ
ActionKeyManager::~ActionKeyManager()
{FUNCLOG}

// キー入力状態を初期化
void ActionKeyManager::initKeyStatus()
{
	FUNCLOG
	for(int i = 0; i < static_cast<int>(Key::SIZE) ; this->keyStatus[static_cast<Key>(i)] = 0.f, i++);
	return;
}

// キーを押しているか判別
bool ActionKeyManager::isPressed(Key key, float second = 0)
{
	FUNCLOG
	return (this->keyStatus.at(key) <= second && this->keyStatus.at(key) != 0);
}

// 1ループにかかる時間でキーステータスを更新
void ActionKeyManager::updateKeyStatus(float delta)
{
	FUNCLOG
	for (auto itr = this->keyStatus.begin(); itr != this->keyStatus.end(); ++itr)
	{	
		if (itr->second > 0.f) itr->second += delta;
	}
	return;
}