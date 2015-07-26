//
//  baseSaveDataSelector.h
//  LastSupper
//
//  Created by Kohei on 2015/07/20.
//
//

#ifndef __BASE_SAVE_DATA_SELECTOR_H__
#define __BASE_SAVE_DATA_SELECTOR_H__

#include "Common.h"
#include "Layers/baseMenuLayer.h"

class baseSaveDataSelector : public baseMenuLayer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(baseSaveDataSelector, vector<string>);
	virtual bool init(const vector<string> datas);
	
	// クラス変数
private:
	static const int H_MARGIN;
	static const int V_MARGIN;
	static const int MAX_V_CNT;
	static const int EACH_V_MARGIN;
	
	// インスタンスメソッド
public:
	baseSaveDataSelector();
	~baseSaveDataSelector();
	virtual void moveCursor(bool sound);
	virtual void onSpacePressed();

};

#endif // __BASE_SAVE_DATA_SELECTOR_H__
