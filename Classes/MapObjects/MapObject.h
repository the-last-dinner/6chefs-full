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

class MapObject : public Node
{
	// 定数
public:
	static const Color3B TORCH_COLOR;

	// インスタンス変数
private:
	Size objectSize { Size::ZERO };
	int eventId { -1 };
	TriggerType trigger {TriggerType::SIZE};
	bool _isHit { false };
	Direction movingDirection {Direction::SIZE};
	Light* light { nullptr };
	
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
	void setLight(Light* light);
	void removeLight();
	
	Point getGridPosition(const Size& mapSize);
	Size getObjectSize();
	int getEventId();
	TriggerType getTrigger();
	bool isHit();
	Direction getMovingDirection();
};

#endif // __MAP_OBJECT_H__
