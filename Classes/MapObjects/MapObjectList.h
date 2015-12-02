//
//  MapObjectList.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/10/02.
//
//

#ifndef __LastSupper__MapObjectList__
#define __LastSupper__MapObjectList__

#include "Common.h"

#include "MapObjects/MapObject.h"
#include "MapObjects/Enemy.h"
#include "MapObjects/TerrainObject/TerrainObject.h"

class Party;
class PlainArea;

class MapObjectList : public Node
{
// クラスメソッド
public:
    static MapObjectList* create(const Vector<MapObject*>& availableObjects, const Vector<MapObject*> disableObjects, const Vector<TerrainObject*> terrainObjects);
    
// インスタンス変数
private:
    Vector<MapObject*> availableObjects {};
    Vector<MapObject*> disableObjects {};
    Party* party { nullptr };
    Vector<Enemy*> enemies {};
    Vector<TerrainObject*> terrainObjects {};
    function<void()> onContactWithEnemy { nullptr };
    PlainArea* plainArea { nullptr };
    
// インスタンスメソッド
private:
    MapObjectList();
    ~MapObjectList();
    bool init(const Vector<MapObject*>& availableObjects, const Vector<MapObject*> disableObjects, const Vector<TerrainObject*> terrainObjects);
public:
    MapObject* getMapObject(int objId) const;
    MapObject* getMapObjectFromDisableList(int objId) const;
    const Vector<MapObject*>& getMapObjects() const;
    const bool containsCollisionObject(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Rect& rect) const;
    Vector<MapObject*> getMapObjects(const Point& position) const;
    Vector<MapObject*> getMapObjectsByGridRect(const Rect& gridRect, const Trigger trigger = Trigger::SIZE) const;
    
    vector<int> getEventIds(const Trigger trigger) const;
    vector<int> getEventIdsByGridRect(const Rect& gridRect, const Trigger trigger) const;
    vector<Rect> getGridCollisionRects() const;
    
    // 追加、削除
    void add(MapObject* mapObject);
    void removeById(const int objectId);
    
    // 敵
    void addEnemy(Enemy* enemy);
    void removeEnemyById(const int enemyId);
    Vector<Enemy*> getEnemiesAll();
    bool existsEnemy() const;
    
    // 主人公一行
    void setParty(Party* party);
    Party* getParty();
    void onPartyMoved(const Rect& gridRect);
    
    // 地形
    TerrainObject* getTerrainByGridRect(const Rect& gridRect);

    // 敵と主人公一行の衝突監視用updateメソッド
    void update(float delta);
};

#endif /* defined(__LastSupper__MapObjectList__) */
