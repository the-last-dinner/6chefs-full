//
//  TiledMapLayer.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#include "TiledMapLayer.h"

// コンストラクタ
TiledMapLayer::TiledMapLayer():
data(nullptr),
parentListener(nullptr)
{FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer()
{FUNCLOG}

// create関数
TiledMapLayer* TiledMapLayer::create(const string& mapFileName, EventListenerKeyboard* listener)
{
	TiledMapLayer* pRet = new TiledMapLayer();
	if (pRet && pRet->init(mapFileName, listener)) {
		pRet->autorelease();
		return pRet;
	}
	else {
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

// 初期化
bool TiledMapLayer::init(const string& mapFileName, EventListenerKeyboard* listener)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// ダンジョンシーンに登録しているイベントリスナーのIDをセット
	this->parentListener = listener;
	
	// データクラス初期化
	this->data = new TiledMapData(mapFileName);
	
	// TiledのマップをaddChild
	experimental::TMXTiledMap* map = this->data->getTiledMap();
	map->setOpacity(0);
	map->setZOrder(static_cast<int>(Priority::MAP));
	this->addChild(map);
	
	// カメラを主人公中心にセット
	Point center = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	//map->setPosition(center - map->getChildByName<Character*>("main")->getPosition());
	
	// メッセージウインドウテスト
	queue<string> pages;
	pages.push("あいうえお\nテステステウテス\n会合\n改行");
	pages.push("かきくけこ");
	CharacterMessageLayer* messageLayer = CharacterMessageLayer::createWithName("テスト君", pages);
	this->addChild(messageLayer);
	this->parentListener->setEnabled(false);
	messageLayer->setCallback([=](){this->parentListener->setEnabled(true);});
	messageLayer->start();

	return true;
}

// 主人公の操作
void TiledMapLayer::controlMainCharacter(ActionKeyManager::Key key)
{
	FUNCLOG
	switch(key)
	{
		case::ActionKeyManager::Key::DOWN:
		case::ActionKeyManager::Key::LEFT:
		case::ActionKeyManager::Key::RIGHT:
		case::ActionKeyManager::Key::UP:
		{
			ActionKeyManager* manager = ActionKeyManager::getInstance();
			experimental::TMXTiledMap* map = this->data->getTiledMap();
			Character* main = map->getChildByName<Character*>("main");
			
				
			// 移動キーが押された時は、向きを変える
			Direction direction = static_cast<Direction>(key);
			main->setDirection(direction);
			
			// 動いてる向きを取得
			Direction movingDirection = main->getMovingDirection();
			// ループを解除
			this->unschedule("ControlCheck");
			
			// ループを開始
			this->schedule([=](float delta){
				if(ActionKeyManager::getInstance()->isPressed(key))
				{
					// 主人公が動いていない、向きがキーを押した時と同じ、その方向に当たり判定がなかったら
					if(!main->isMoving() && main->getDirection() == direction && !this->data->isHit(main, direction))
					{
						Direction moveDirection = manager->getMoveDirection(movingDirection, key);
						Point movement = movementMap.at(moveDirection);
						this->runAction(Sequence::create(Spawn::create(CallFunc::create([=](){main->stamp();main->setMovingDirection(moveDirection);}),
																	   TargetedAction::create(map, MoveBy::create(Character::SECOND_PER_GRID, - movement)),
																	   TargetedAction::create(main, MoveBy::create(Character::SECOND_PER_GRID, movement)),
																	   nullptr),
														 CallFunc::create([=](){main->setMovingDirection(Direction::NONE);}),
														 nullptr));
					}
				}
				else
				{
					// キーを離したらループを解除
					this->unschedule("ControlCheck");
				}
					
			}, ActionKeyManager::INPUT_CHECK_SPAN, "ControlCheck");
			
			break;
		}
		case::ActionKeyManager::Key::SPACE:
			break;
		default:
			break;
	}

}