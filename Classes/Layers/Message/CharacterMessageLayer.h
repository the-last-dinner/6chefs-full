//
//  CharacterMessageLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/07/12.
//
//

#ifndef __CHARACTER_MESSAGE_LAYER_H__
#define __CHARACTER_MESSAGE_LAYER_H__

#include "Layers/Message/baseMessageLayer.h"

#include "cocos-ext.h"

class CharacterMessageLayer : public baseMessageLayer
{
// 列挙型
public:
    enum struct Option
    {
        REACTION,
        
        SIZE
    };
// 構造体
public:
    struct Information
    {
        int charaId {-1};
        int imgId {-1};
        string charaName { "" };
        queue<string> pages {};
        Option option {Option::SIZE};
    };
    
// 定数
private:
    static constexpr float TOP_MARGIN {50};
    static constexpr float LEFT_MARGIN {60};
    static constexpr float H_MARGIN_S {30};
    
// クラスメソッド
public:
    CREATE_FUNC_WITH_PARAM(CharacterMessageLayer, const queue<Information>&);
	
// インスタンス変数
private:
    queue<Information> infos {};
    ui::Scale9Sprite* nameFrame { nullptr };

// インスタンスメソッド
private:
	CharacterMessageLayer();
	~CharacterMessageLayer();
    virtual bool init(const queue<Information>& infos);
	virtual void createMessage() override;
    virtual void onAllPageDisplayed() override;
};

#endif // __CHARACTER_MESSAGE_LAYER_H__
