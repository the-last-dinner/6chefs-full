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
	
	// インスタンス変数
private:
	Size objectSize;
	
	// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	Point getGridPosition();
	void setGridPosition(const Point& mapGridPoint);
	bool isHit(const Direction direction);
	void setObjectSize(const Size& objSize);
};

#endif // __MAP_OBJECT_H__
