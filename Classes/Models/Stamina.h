//
//  Stamina.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/29.
//
//

#ifndef Stamina_h
#define Stamina_h

#include "define.h"

class Stamina : public Ref
{
// 定数
public:
    static const float MAX_VALUE;
    static const float MIN_VALUE;
    static const float DEFAULT_STEP;
    static const float INCREASE_STEP_RATIO;
    static const float INCREASE_UPDATE_INTERVAL;
    
// クラスメソッド
public:
    CREATE_FUNC(Stamina)
    
// インスタンス変数
private:
    float percentage { MAX_VALUE };
    float step { DEFAULT_STEP };
    bool decreasing {false};
public:
    function<void(float)> onPercentageChanged { nullptr };
    
// インスタンスメソッド
private:
    Stamina();
    ~Stamina();
    bool init();
    void increase();
    void setPercentage(const float percentage);
public:
    float getPercentage() const;
    void decrease();
    bool isEmpty() const;
    bool isMax() const;
    void update(float delta);
};

#endif /* Stamina_h */
