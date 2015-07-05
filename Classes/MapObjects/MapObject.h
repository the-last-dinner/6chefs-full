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
	};
	
	// インスタンス変数
private:
	Size objectSize;
public:
	int eventId;
	TriggerType trigger;
	
	// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	Point getGridPosition(const Size& mapSize);
	void setGridPosition(const Size& mapSize, const Point& mapGridPoint);
	bool isHit(const Direction direction);
	void setObjectSize(const Size& objSize);
	void setEventId(int eventId);
	void setTrigger(TriggerType trigger);
};

#endif // __MAP_OBJECT_H__
