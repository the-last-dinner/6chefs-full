//
//  StaminaBar.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/30.
//
//

#ifndef StaminaBar_h
#define StaminaBar_h

#include "UI/SlideNode.h"

class StaminaBar : public SlideNode
{
// 定数
private:
    static const float HORIZONTAL_MARGIN;
    static const float VERTICAL_MARGIN;
    
// クラスメソッド
public:
    CREATE_FUNC(StaminaBar)

// インスタンス変数
private:
    ProgressTimer* progressTimer { nullptr };
    
// インスタンスメソッド
private:
    StaminaBar();
    ~StaminaBar();
    bool init();

public:
    void setPercentage(const float percentage);
    virtual void slideIn(AnimationCallback cb = nullptr) override;
    virtual void slideOut(AnimationCallback cb = nullptr) override;
};

#endif /* ProgressBar_h */
