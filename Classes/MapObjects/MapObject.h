//
//  MapObject.h
//  LastSupper
//
//  Created by Kohei on 2015/06/21.
//
//

#ifndef __MAP_OBJECT_H__
#define __MAP_OBJECT_H__

#include "Common.h"

class Light;
class AmbientLightLayer;
class MapObjectList;

class MapObject : public Node
{
// インスタンス変数
private:
    int eventId { static_cast<int>(EventID::UNDIFINED) };
	Trigger trigger {Trigger::SIZE};
	bool _isHit { false };
	Direction movingDirection {Direction::SIZE};
    Rect collisionRect {Rect::ZERO};
	Light* light { nullptr };
    MapObjectList* objectList { nullptr };
	
// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	void setGridPosition(const Size& mapSize, const Point& mapGridPoint);
	void setEventId(int eventId);
	void setTrigger(Trigger trigger);
	void setHit(bool _isHit);
	void setMovingDirection(Direction direction);
    void setCollisionRect(const Rect& rect);
    void setMapObjectList(MapObjectList* objectList);
    
	void setLight(Light* light, AmbientLightLayer* ambientLightLayer);
	void removeLight();
	
    Size  getGridSize() const;
	Point getGridPosition(const Size& mapSize) const;
	int getEventId();
	Trigger getTrigger();
	const bool isHit() const;
    const bool isHit(const Direction& direction) const;
    const bool isHit(const Direction (&directions)[2]) const;
	Direction getMovingDirection();
    Rect getCollisionRect() const;
    Rect getCollisionRect(const Direction& direction) const;
    Rect getCollisionRect(const Direction (&directions)[2]) const;

    void drawDebugMask(); // デバッグ用マスク
};

#endif // __MAP_OBJECT_H__
