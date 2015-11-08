//
//  MiniSelector.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/08.
//
//

#ifndef MiniSelector_h
#define MiniSelector_h

#include "Layers/Menu/MenuLayer.h"

class MiniSelector;

class MiniSelector: public MenuLayer
{
public:
    // ミニ選択ウインドウ設定構造体
    struct Selector
    {
    private:
        Point index {Point(0,0)};
        Color3B color {Color3B::WHITE}; // 文字色
        Color3B background_color {Color3B::BLACK}; // 背景色
        Color3B rectangle_color {Color3B::WHITE}; // 枠色
        SpriteUtils::Square position {SpriteUtils::Square(0,0,0,0)}; // 位置
        SpriteUtils::Margin margin {SpriteUtils::Margin(3.0)}; // margin
        vector<string> menu {nullptr}; // menuのインデックス
    public:
        Selector(const Point index, const SpriteUtils::Square position, vector<string>& menu):index(index),position(position),menu(menu){}
        Selector(const Point index, const SpriteUtils::Square position, vector<string>& menu, const SpriteUtils::Margin& margin):index(index),position(position),menu(menu),margin(margin){}
        void setColor(Color3B color){this->color = color;};
        void setBackgroundColor(Color3B color){this->background_color = color;};
        void setRectangleColor(Color3B color){this->rectangle_color = color;};
        const Point getIndexSize(){return index;};
        const Size getWindowSize(){return Size(position.getWidth(),position.getHeight());};
        const SpriteUtils::Square getPosition(){return position;};
        const SpriteUtils::Margin getMargin(){return margin;};
        const vector<string> getMenu(){return menu;};
        const Color3B getColor(){return color;};
        const Color3B getBackgroundColor(){return background_color;};
        const Color3B getRectangleColor(){return rectangle_color;};
    };
    // クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(MiniSelector, Selector&)
    virtual bool init(Selector& selector);
    
    // クラス変数
private:
    static const float INNER_H_MARGIN_RATIO;
    static const float INNER_V_MARGIN_RATIO;
    
    // インスタンスメソッド
private:
    virtual void onIndexChanged(int newIdx, bool sound);
    virtual void onSpacePressed(int idx);
    virtual void onMenuKeyPressed();
    void changeItemDiscription(const int idx);
protected:
    MiniSelector();
    ~MiniSelector();
public:
    virtual void show() override;
    virtual void hide() override;
    // インスタンス変数
public:
    function<void()> onMiniSelectorCanceled { nullptr };
    function<void(int index)> onMiniIndexSelected {nullptr};
};

#endif /* MiniSelector_h */
