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
// 定数
public:
    static const float DURATION_MOVE_ONE_GRID;
    
// インスタンス変数
private:
    int objectId { static_cast<int>(ObjectID::UNDIFINED)};
    int eventId { static_cast<int>(EventID::UNDIFINED) };
	Trigger trigger {Trigger::SIZE};
	bool _isHit { false };
    Rect collisionRect {Rect::ZERO};
	Light* light { nullptr };
    MapObjectList* objectList { nullptr };
    Point gridPosition {Point::ZERO};
    bool _isMoving { false };
protected:
    deque<vector<Direction>> directionsQueue {};
public:
    function<void(MapObject*)> onMove { nullptr };
	
// インスタンスメソッド
public:
	MapObject();
	~MapObject();
	void setGridPosition(const Point& gridPosition);
    void setObjectId(int objectId);
	void setEventId(int eventId);
	void setTrigger(Trigger trigger);
	void setHit(bool _isHit);
    void setCollisionRect(const Rect& rect);
    void setMapObjectList(MapObjectList* objectList);
    
	void setLight(Light* light, AmbientLightLayer* ambientLightLayer);
	void removeLight();
	
    Size  getGridSize() const;
	Point getGridPosition() const;
    Rect getGridRect() const;
    int getObjectId() const;
	int getEventId() const;
	Trigger getTrigger() const;
    bool isMoving() const;
    
    // collision
	const bool isHit() const;
    const bool isHit(const Direction& direction) const;
    const bool isHit(const vector<Direction>& directions) const;
    Rect getCollisionRect() const;
    Rect getCollisionRect(const Direction& direction) const;
    Rect getCollisionRect(const vector<Direction>& directions) const;

    // move
    bool moveBy(const Direction& direction, function<void()> onMoved, const float ratio = 1.0f);
    bool moveBy(const vector<Direction>& directions, function<void()> onMoved, const float ratio = 1.0f);
    void moveBy(const Direction& direction, const int gridNum, function<void(bool)> onMoved, const float ratio = 1.0f);
    void moveBy(const vector<Direction>& directions, const int gridNum, function<void(bool)> onMoved, const float ratio = 1.0f);
    void moveByQueue(deque<vector<Direction>> directionsQueue, function<void(bool)> callback, const float ratio = 1.0f);
    void clearDirectionsQueue();
    
    // イベント関数
    virtual void onEnterMap() {};                               // マップに追加された時

    void drawDebugMask(); // デバッグ用マスク
};

#endif // __MAP_OBJECT_H__
