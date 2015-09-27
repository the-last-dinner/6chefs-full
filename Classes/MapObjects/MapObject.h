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

class MapObject : public Node
{
// 定数
public:
    enum EventID
    {
        UNDIFINED = -1,
    };
// インスタンス変数
private:
    int eventId { EventID::UNDIFINED };
	Trigger trigger {Trigger::SIZE};
	bool _isHit { false };
	Direction movingDirection {Direction::SIZE};
	Light* light { nullptr };
	
// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	void setGridPosition(const Size& mapSize, const Point& mapGridPoint);
	void setEventId(int eventId);
	void setTrigger(Trigger trigger);
	void setHit(bool _isHit);
	void setMovingDirection(Direction direction);
	void setLight(Light* light, AmbientLightLayer* ambientLightLayer);
	void removeLight();
	
	Point getGridPosition(const Size& mapSize);
	int getEventId();
	Trigger getTrigger();
	bool isHit();
	Direction getMovingDirection();
    
    void drawDebugMask();
};

#endif // __MAP_OBJECT_H__
