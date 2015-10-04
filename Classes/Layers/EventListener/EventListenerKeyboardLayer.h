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
    function<void(const vector<Key>& keys)> intervalInputCheck { nullptr };
private:
    EventListenerKeyboard* listenerKeyboard { nullptr };
    map<Key, bool> keyStatus {};
    vector<Key> pressingKeys {};
    float delay {0.05f};        // キーを押した瞬間から初回キー入力確認までの時間
    float interval {0.05f};     // キー入力の確認間隔
    
// インスタンスメソッド
public:
    EventListenerKeyboardLayer();   // コンストラクタ
    ~EventListenerKeyboardLayer();  // デストラクタ
    virtual bool init() override;    // 初期化
    void setEnabled(bool enabled);    // リスナを有効/無効化
    void setInputCheckDelay(float delay);               // キーを押した瞬間から初回キー入力確認までの時間を設定
    void setInputCheckInterval(float interval);         // キー入力の確認間隔を設定
    void onKeyPressed(const EventKeyboard::KeyCode& keyCode);      // キーを押した時
    void onKeyReleased(const EventKeyboard::KeyCode& keyCode);     // キーを離した時
    void releaseKey(const Key key);  // キーを離すとき
    void releaseKeyAll();  // 全てのキーをリリース状態にリセット
    void inputCheck(float duration);                        // キーを押し続けている時
    bool isPressed(const Key& key);                                // 指定キーが押し状態か判別
    Key convertKeyCode(const EventKeyboard::KeyCode& keyCode);     // cococs上でのキーコードをゲーム内キーに変換

};

#endif /* defined(_EventListenerKeyboardLayer__) */
