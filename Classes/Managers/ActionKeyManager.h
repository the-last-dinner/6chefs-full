#ifndef  __ACTION_KEY_MANAGER_H__
#define __ACTION_KEY_MANAGER_H__

#include "define.h"

class ActionKeyManager
{
	// 構造体、列挙型
public:
	enum struct Key
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		MENU,
		DASH,
		SPACE,
		SIZE
	};

	// クラスメソッド
public:
	static ActionKeyManager* getInstance();
	static void destroy();
	
	// クラス変数
private:
	static const map<EventKeyboard::KeyCode, Key> keyMap;

	// インスタンスメソッド
private:
	ActionKeyManager();													// コンストラクタ
	ActionKeyManager(const ActionManager& other);						// コピーコンストラクタ
	ActionKeyManager& operator = (const ActionKeyManager& other);		// 代入演算子
public:
	~ActionKeyManager();
	bool isPressed(Key key, float second);
	void updateKeyStatus(float delta);
	void initKeyStatus();
	
	// インスタンス変数
private:
	map<Key, float> keyStatus;
};

#endif // __ACTION_KEY_MANAGER_H__