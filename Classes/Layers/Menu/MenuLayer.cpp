//
//  MenuLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/05.
//
//

#include "Layers/Menu/MenuLayer.h"

#include "Layers/EventListener/EventListenerKeyboardLayer.h"

// コンストラクタ
MenuLayer::MenuLayer(){FUNCLOG}

// デストラクタ
MenuLayer::~MenuLayer(){FUNCLOG}

// 初期化
bool MenuLayer::init(const Point& index, const Size& size)
{
	this->indexX = index.x;
	this->indexY = index.y;
	
	return this->init(size.width, size.height);
}

// 初期化
bool MenuLayer::init(int sizeX, int sizeY)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// メニューの項目数を設定
	this->sizeX = sizeX;
	this->sizeY = sizeY;
    
    EventListenerKeyboardLayer* listenerKeyboard { EventListenerKeyboardLayer::create() };
    listenerKeyboard->onCursorKeyPressed = CC_CALLBACK_1(MenuLayer::onCursorKeyPressed, this);
    listenerKeyboard->onSpaceKeyPressed = CC_CALLBACK_0(MenuLayer::onSpaceKeyPressed, this);
    listenerKeyboard->onMenuKeyPressed = CC_CALLBACK_0(MenuLayer::onMenuKeyPressed, this);
    listenerKeyboard->setEnabled(false);
    this->addChild(listenerKeyboard);
    this->listenerKeyboard = listenerKeyboard;

	return true;
}

// 方向キーを押した時
void MenuLayer::onCursorKeyPressed(const Key& key)
{
    switch(key)
    {
        case Key::UP:
            if(sizeY >= 2) this->indexY = (indexY == 0)? indexY = sizeY - 1 : (indexY - 1) % sizeY;
            this->onIndexChanged(this->getSelectedIndex());
            break;
            
        case Key::DOWN:
            if(sizeY >= 2) this->indexY = (indexY + 1) % sizeY;
            this->onIndexChanged(this->getSelectedIndex());
            break;
            
        case Key::LEFT:
            if(sizeX >= 2) this->indexX = (indexX == 0)? indexX = sizeX - 1 : (indexX - 1) % sizeX;
            this->onIndexChanged(this->getSelectedIndex());
            break;
            
        case Key::RIGHT:
            if(sizeX >= 2) this->indexX = (indexX + 1) % sizeX;
            this->onIndexChanged(this->getSelectedIndex());
            break;
            
        default:
            break;
    }
}

// スペースを押した時
void MenuLayer::onSpaceKeyPressed()
{
    this->onSpacePressed(this->getSelectedIndex());
}

// 現在選ばれているメニューのINDEXを取得(現時点では横優先配置の場合のみ)
int MenuLayer::getSelectedIndex() const
{return sizeX * indexY + indexX;}

// メニューサイズの横方向を取得
int MenuLayer::getMenuSizeX() const
{return this->sizeX;}

// メニューサイズの縦方向を取得
int MenuLayer::getMenuSizeY() const
{return this->sizeY;}