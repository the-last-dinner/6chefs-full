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
// クラスメソッド
public:
    CREATE_FUNC_WITH_TWO_PARAM(StaminaBar, const Point&, const Point&)

// インスタンス変数
private:
    ProgressTimer* progressTimer { nullptr };
    
// インスタンスメソッド
private:
    StaminaBar();
    ~StaminaBar();
    virtual bool init(const Point& inPosition, const point& outPosition) override;

public:
    void setPercentage(const float percentage);
    virtual void slideIn(AnimationCallback cb = nullptr) override;
    virtual void slideOut(AnimationCallback cb = nullptr) override;
};

#endif /* ProgressBar_h */
