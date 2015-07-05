//
//  TiledMapLayer.h
//  LastSupper
//
//  Created by Kohei on 2015/06/28.
//
//

#ifndef __TILED_MAP_LAYER_H__
#define __TILED_MAP_LAYER_H__

#include "Common.h"
#include "Datas/Layer/TiledMapData.h"

class TiledMapLayer : public Layer
{
	// クラスメソッド
public:
	static Layer* create(const string& mapFileName);
	
	// インスタンスメソッド
private:
	TiledMapLayer();
	~TiledMapLayer();
	bool init(const string& mapFileName);
	
	// インスタンス変数
private:
	TiledMapData* data;
};

#endif // __TILED_MAP_LAYER_H__
