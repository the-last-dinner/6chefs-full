//
//  TitleSelectMenuLayer.h
//  6chefs
//
//  Created by Kohei Asami on 2017/09/17.
//
//

#ifndef TitleSelectMenuLayer_h
#define TitleSelectMenuLayer_h

#include "Layers/Menu/MenuLayer.h"

class TitleSelectMenuLayer : public MenuLayer
{
// 定数
private:
    static const string TITLE_NODE_NAME;
    static const string CURSOR_NODE_NAME;
    static const string CHARA_NODE_NAME;
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(TitleSelectMenuLayer, function<void(int)>)
// インスタンスメソッド
public:
    virtual void show() override;
    virtual void hide() override;
private:
    TitleSelectMenuLayer();
    ~TitleSelectMenuLayer();
    virtual bool init(function<void(int)> onSelectTitle);
    virtual void onIndexChanged(int newIdx, bool sound = true) override;
    virtual void onEnterKeyPressed(int idx) override;
    void onShowAnimationFinished();
// インスタンス変数
private:
    function<void(int)> _onSelectTitle { nullptr };
    Sprite* _bg { nullptr };
    Layer* _layer1 { nullptr };
    Layer* _layer2 { nullptr };
};

#endif /* TitleSelectMenuLayer_h */
