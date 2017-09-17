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

class TitleSelectPanel;

class TitleSelectMenuLayer : public MenuLayer
{
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
    vector<TitleSelectPanel*> _panels {};
};

#endif /* TitleSelectMenuLayer_h */
