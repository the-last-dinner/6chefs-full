#include "Managers/ActionKeyManager.h"

// キー変換用連想配列
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

// キー入力をチェックするスパン
const float ActionKeyManager::INPUT_CHECK_SPAN = 0.02f;

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
	this->keyStatus.clear();
	for(int i = 0; i < static_cast<int>(Key::SIZE); this->keyStatus[static_cast<Key>(i)] = false, i++);
	return;
}

// キーコードを変換。ゲームで使わないキーが与えられた場合はOTHERを返す
ActionKeyManager::Key ActionKeyManager::convertKeyCode(EventKeyboard::KeyCode keyCode)
{return (keyMap.count(keyCode) == 0)?Key::OTHER:keyMap.at(keyCode);}

// 指定のキーを押し状態に。
void ActionKeyManager::pressKey(Key key)
{this->keyStatus.at(key) = true;return;}

// 指定のキーを離し状態に
void ActionKeyManager::releaseKey(Key key)
{this->keyStatus.at(key) = false;return;}

// 指定のキーが押し状態か判別
bool ActionKeyManager::isPressed(Key key)
{return this->keyStatus.at(key);}

// // 現在主人公が進んでいる方向と、新たに押されたキーから、移動方向を返す
Direction ActionKeyManager::getMoveDirection(Direction direction, Key key)
{
	int directionAsInt = static_cast<int>(direction);
	int keyAsInt = static_cast<int>(key);
	if(directionAsInt > static_cast<int>(Direction::SIZE) || directionAsInt == keyAsInt || fabs(directionAsInt - keyAsInt) > 2) return static_cast<Direction>(key);
	
	// 斜め可能なパターンであるとき
	int minVal = min(directionAsInt, keyAsInt);
	if(minVal == 0) return static_cast<Direction>(directionAsInt + keyAsInt + 4);
	return static_cast<Direction>(max(directionAsInt, keyAsInt) * 2 + minVal);
}