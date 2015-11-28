//
//  SlideNode.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/27.
//
//

#ifndef SlideNode_h
#define SlideNode_h

#include "define.h"

class SlideNode : public Node
{
    //定数
    using AnimationCallback = function<void(SlideNode*)>;
    
    // クラスメソッド
public:
    CREATE_FUNC_WITH_TWO_PARAM(SlideNode, const Point&, const Point&)
private:
    SlideNode(){FUNCLOG};
    ~SlideNode(){FUNCLOG};
    
    // インスタンス変数
private:
    Point inPosition {Point::ZERO};
    Point outPosition {Point::ZERO};
    float slideTime {0.3f};
    
    // インスタンスメソッド
private:
    bool init(const Point& inPosition, const Point& outPosition);
public:
    void setSlideTime(const float& time);
    void slideIn(AnimationCallback callback = nullptr);
    void slideOut(AnimationCallback callback = nullptr);
    
};

#endif /* SlideNode_h */
