#ifndef  __ACTION_KEY_MANAGER_H__
#define __ACTION_KEY_MANAGER_H__

#include "define.h"

class ActionKeyManager
{
	// 構造体、列挙型
public:
	enum struct Key
	{
		DOWN,
		RIGHT,
		LEFT,
		UP,
		MENU,
		DASH,
		SPACE,
		OTHER,
		SIZE,
	};

	// クラスメソッド
public:
	static ActionKeyManager* getInstance();
	static void destroy();
	
	// クラス変数
private:
	static const map<EventKeyboard::KeyCode, Key> keyMap;
public:
	static const float INPUT_CHECK_SPAN;

	// インスタンスメソッド
private:
	ActionKeyManager();													// コンストラクタ
	ActionKeyManager(const ActionKeyManager& other);					// コピーコンストラクタ
	ActionKeyManager& operator = (const ActionKeyManager& other);		// 代入演算子
public:
	~ActionKeyManager();
	void initKeyStatus();
	void pressKey(Key key);
	void releaseKey(Key key);
	bool isPressed(Key key);
	Key convertKeyCode(EventKeyboard::KeyCode keyCode);
	
	// インスタンス変数
private:
	map<Key, bool> keyStatus;
};

#endif // __ACTION_KEY_MANAGER_H__