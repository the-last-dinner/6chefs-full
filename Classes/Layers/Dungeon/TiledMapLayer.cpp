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
data(nullptr)
{FUNCLOG}

// デストラクタ
TiledMapLayer::~TiledMapLayer()
{FUNCLOG}

// create関数
Layer* TiledMapLayer::create(const string& mapFileName)
{
	TiledMapLayer* pRet = new TiledMapLayer();
	if (pRet && pRet->init(mapFileName)) {
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
bool TiledMapLayer::init(const string& mapFileName)
{
	FUNCLOG
	if(!Layer::init()) return false;
	
	// データクラス初期化
	this->data = new TiledMapData(mapFileName);
	
	// TiledのマップをaddChild
	experimental::TMXTiledMap* map = this->data->getTiledMap();
	map->setOpacity(0);
	this->addChild(map);
	
	// カメラを主人公中心にセット
	Point center = Point(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	map->setPosition(center - map->getChildByName<Character*>("main")->getPosition());
	
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
			experimental::TMXTiledMap* map = this->data->getTiledMap();
			Character* main = map->getChildByName<Character*>("main");
			
				
			// 移動キーが押された時は、向きを変える
			Character::Direction direction = static_cast<MapObject::Direction>(key);
			main->setDirection(direction);
			
			// ループを解除
			this->unschedule("ControlCheck");
			
			// ループを開始
			this->schedule([=](float delta){
				if(ActionKeyManager::getInstance()->isPressed(key))
				{
					// 主人公が動いていない、向きがキーを押した時と同じ、その方向に当たり判定がなかったら
					if(!main->isMoving() && main->getDirection() == direction && !this->data->isHit(main, direction))
					{
						this->runAction(Sequence::create(Spawn::create(CallFunc::create([=](){main->stamp();}),
																	   TargetedAction::create(map, MoveBy::create(Character::SECOND_PER_GRID, - MapObject::gridMap.at(direction))),
																	   TargetedAction::create(main, MoveBy::create(Character::SECOND_PER_GRID, MapObject::gridMap.at(direction))),
																	   nullptr),
														 CallFunc::create([=](){}),
														 nullptr));						}
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