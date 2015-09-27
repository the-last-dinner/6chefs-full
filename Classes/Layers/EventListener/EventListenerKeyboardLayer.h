//
//  EventListenerKeyboardLayer.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/23.
//
//

#ifndef _EventListenerKeyboardLayer__
#define _EventListenerKeyboardLayer__

#include "Common.h"

// PC版共通キーボード用イベントリスナ
class EventListenerKeyboardLayer : public Layer
{
// 定数
private:
    static const map<EventKeyboard::KeyCode, Key> keyMap;
    
// クラスメソッド
public:
    CREATE_FUNC(EventListenerKeyboardLayer);
    
// インスタンス変数
public:
    function<void(const Key&)> onCursorKeyPressed { nullptr };
    function<void()> onSpaceKeyPressed { nullptr };
    function<void()> onMenuKeyPressed { nullptr };
    function<void()> onDashKeyPressed { nullptr };
    function<void(const Key& key)> pressingKey { nullptr };
private:
    EventListenerKeyboard* listenerKeyboard { nullptr };
    map<Key, bool> keyStatus {};
    vector<Key> pressingKeys {};
    float delay {0.05f};
    float interval {0.02f};
    
// インスタンスメソッド
public:
    EventListenerKeyboardLayer();   // コンストラクタ
    ~EventListenerKeyboardLayer();  // デストラクタ
    virtual bool init() override;    // 初期化
    void setEnabled(bool enabled);    // リスナを有効/無効化
    void onKeyPressed(const EventKeyboard::KeyCode& keyCode);      // キーを押した時
    void onKeyReleased(const EventKeyboard::KeyCode& keyCode);     // キーを離した時
    void updatePressingKey(float duration);                        // キーを押し続けている時
    bool isPressed(const Key& key);                                // 指定キーが押し状態か判別
    Key convertKeyCode(const EventKeyboard::KeyCode& keyCode);     // cococs上でのキーコードをゲーム内キーに変換
    Direction getMoveDirection(const Direction& direction, const Key& key);

};

#endif /* defined(_EventListenerKeyboardLayer__) */
