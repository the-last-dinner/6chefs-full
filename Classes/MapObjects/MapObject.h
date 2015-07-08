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
	// 列挙型、構造体
public:
	enum struct Direction
	{
		FRONT,
		RIGHT,
		LEFT,
		BACK,
		SIZE,
	};

	// トリガータイプ
	enum struct TriggerType
	{
		INIT,
		RIDE,
		SEARCH,
		NONE,
		SIZE
	};
	
	// クラス変数
public:
	static const map<MapObject::Direction, Point> gridMap;
	
	// インスタンス変数
private:
	Size objectSize;
	int eventId;
	TriggerType trigger;
	bool _isHit;
	
	// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	void setGridPosition(const Size& mapSize, const Point& mapGridPoint);
	void setObjectSize(const Size& objSize);
	void setEventId(int eventId);
	void setTrigger(TriggerType trigger);
	void setHit(bool _isHit);
	
	Point getGridPosition(const Size& mapSize);
	Size getObjectSize();
	int getEventId();
	TriggerType getTrigger();
	bool isHit();
};

#endif // __MAP_OBJECT_H__
