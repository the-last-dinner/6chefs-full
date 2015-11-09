//
//  CharacterMenuLayer.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/11/09.
//
//

#ifndef CharacterMenuLayer_h
#define CharacterMenuLayer_h

#include "Layers/Menu/MenuLayer.h"

class CharacterMenuLayer : public MenuLayer
{
    // クラスメソッド
public:
    CREATE_FUNC(CharacterMenuLayer)
    virtual bool init();
  
    // インスタンスメソッド
private:
    virtual void onIndexChanged(int newIdx, bool sound);
    virtual void onSpacePressed(int idx);
    virtual void onMenuKeyPressed();
    void changeCharaImage(const int idx);
protected:
    CharacterMenuLayer();
    ~CharacterMenuLayer();
public:
    virtual void show() override;
    virtual void hide() override;
    
    // インスタンス変数
private:
    vector<int> characters {};
    int selected_character {0};
    bool isDiscription {false};
public:
    function<void()> onCharacterMenuCanceled { nullptr };
};
#endif /* CharacterMenuLayer_h */
