//
//  MapObject.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/21.
//
//

#include "MapObjects/MapObject.h"

#include "Effects/AmbientLightLayer.h"
#include "Effects/Light.h"

// コンストラクタ
MapObject::MapObject(){FUNCLOG}

// デストラクタ
MapObject::~MapObject(){FUNCLOG}

// マップ上のマス座標を取得(一番左下のマス座標を返す)
Point MapObject::getGridPosition(const Size& mapSize)
{
	return MapUtils::convertToMapPoint(mapSize, Point(this->getPositionX() - this->getContentSize().width / 2, this->getPositionY())) / GRID;
}

// マップ上のマス座標にセット
void MapObject::setGridPosition(const Size& mapSize, const Point& mapGridPoint)
{
	Point cocosPoint = MapUtils::convertToCCPoint(mapSize, mapGridPoint);
	this->setPosition(cocosPoint.x + this->getContentSize().width / 2, cocosPoint.y);
	return;
}

// イベントIDをセット
void MapObject::setEventId(int eventId)
{
	this->eventId = eventId;
	return;
}

// イベントのtriggerをセット
void MapObject::setTrigger(Trigger trigger)
{
	this->trigger = trigger;
	return;
}

// 当たり判定の有無をセット
void MapObject::setHit(bool _isHit)
{
	this->_isHit = _isHit;
	return;
}

// 動いている方向をセット
void MapObject::setMovingDirection(Direction direction)
{
	this->movingDirection = direction;
	return;
}

// ライトをセット
void MapObject::setLight(Light* light, AmbientLightLayer* ambientLightLayer)
{
	this->light = light;
	this->addChild(light);
	//light->setPosition(this->getContentSize() / 2);
	light->setOpacity(0);
	this->runAction(TargetedAction::create(light, FadeIn::create(0.5f)));
    
    // 環境光レイヤーに光源として追加
    ambientLightLayer->addLightSource(this, light->getInformation());
}

// ライトを消す
void MapObject::removeLight()
{
	this->runAction(Sequence::createWithTwoActions(TargetedAction::create(this->light, FadeOut::create(0.5f)), TargetedAction::create(this->light, RemoveSelf::create())));
}

// イベントIDを取得
int MapObject::getEventId()
{return this->eventId;}

// triggerを取得
Trigger MapObject::getTrigger()
{return this->trigger;}

// 当たり判定の有無を取得
bool MapObject::isHit()
{return this->_isHit;}

// 動いている方向を取得
Direction MapObject::getMovingDirection()
{return this->movingDirection;}

// デバッッグ用に枠を描画
void MapObject::drawDebugMask()
{
    Point vertices[]
    {
        Point::ZERO,
        Point(0, this->getContentSize().height),
        this->getContentSize(),
        Point(this->getContentSize().width, 0),
        Point::ZERO
    };
    Color4F lineColor = Color4F::WHITE;
    DrawNode* draw {DrawNode::create()};
    draw->drawPolygon(vertices, 5, Color4F(0,0,0,0), 1, lineColor);
    this->addChild(draw);
}