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

class MiniSelector: public MenuLayer
{
    // クラスメソッド
public:
    CREATE_FUNC(MiniSelector)
    virtual bool init();
    
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
    
};

#endif /* MiniSelector_h */
