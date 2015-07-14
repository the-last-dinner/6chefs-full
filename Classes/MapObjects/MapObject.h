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

class MapObject : public Node
{
	// インスタンス変数
private:
	Size objectSize;
	int eventId;
	TriggerType trigger;
	bool _isHit;
	Direction movingDirection;
	
	// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	void setGridPosition(const Size& mapSize, const Point& mapGridPoint);
	void setObjectSize(const Size& objSize);
	void setEventId(int eventId);
	void setTrigger(TriggerType trigger);
	void setHit(bool _isHit);
	void setMovingDirection(Direction direction);
	
	Point getGridPosition(const Size& mapSize);
	Size getObjectSize();
	int getEventId();
	TriggerType getTrigger();
	bool isHit();
	Direction getMovingDirection();
};

#endif // __MAP_OBJECT_H__
