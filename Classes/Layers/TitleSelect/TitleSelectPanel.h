//
//  TitleSelectPanel.h
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#ifndef TitleSelectPanel_h
#define TitleSelectPanel_h

#include "define.h"

class TitleSelectPanel : public Node
{
// 定数
public:
    enum struct TYPE
    {
        ONE,
        TWO,
    };
private:
    static const map<TYPE, string> TYPE_TO_TITLE_SPRITE_FRAME_NAME;
    static const map<TYPE, string> TYPE_TO_CHARA_SPRITE_FRAME_NAME;
    static const map<TYPE, Point> TYPE_TO_TITLE_POSITION;
    static const map<TYPE, Point> TYPE_TO_CHARA_POSITION;
    static const int FOCUSED_CHARA_Z_ORDER;
    static const int UNFOCUSED_CHARA_Z_ORDER;
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(TitleSelectPanel, TitleSelectPanel::TYPE);
// インスタンスメソッド
public:
    void show(function<void()> callback = nullptr);
    void onFocused(function<void()> callback = nullptr);
    void onUnFocused(function<void()> callback = nullptr);
private:
    TitleSelectPanel();
    ~TitleSelectPanel();
    virtual bool init(TYPE type);
// インスタンス変数
private:
    Sprite* _cursor { nullptr };
    Sprite* _chara { nullptr };
};

#endif /* TitleSelectPanel_h */
