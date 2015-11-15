//
//  SelectEventLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/11/15.
//
//

#include "Layers/Dungeon/SelectEventLayer.h"

#include "Datas/Message/SystemMessageData.h"

#include "Layers/Message/SystemMessageLayer.h"
#include "Layers/Menu/MiniSelector.h"

// コンストラクタ
SelectEventLayer::SelectEventLayer() {FUNCLOG};

// デストラクタ
SelectEventLayer::~SelectEventLayer() {FUNCLOG};

// 初期化
bool SelectEventLayer::init(const string& message, const vector<string>& choices)
{
    if(!Layer::init()) return false;
    
    this->setCascadeOpacityEnabled(true);
    
    // システムメッセージで質問文表示
    SystemMessageLayer* messageLayer { SystemMessageLayer::create(SystemMessageData::create(message), nullptr) };
    this->addChild(messageLayer);
    
    // 選択レイヤ表示
    Point index = Point(1,choices.size()); // 要素数
    SpriteUtils::Square position = SpriteUtils::Square(80, 20, 100, 40); // 位置
    MiniSelector::Selector selector = MiniSelector::Selector(index, position, choices);
    MiniSelector* mini = {MiniSelector::create(selector)};
    mini->show();
    mini->onMiniIndexSelected = CC_CALLBACK_1(SelectEventLayer::onChoiceSelected, this);
    
    this->addChild(mini);
    this->mini = mini;
    
    return true;
}

// 選択肢が選ばれた時
void SelectEventLayer::onChoiceSelected(const int idx)
{
    // MIniSelectorのリスナを無効に
    this->mini->hide();
    
    if(this->onSelected)
    {
        this->onSelected(idx);
    }
    
    this->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f), RemoveSelf::create()));
}
