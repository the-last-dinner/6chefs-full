//
//  SaveDataSelector.h
//  LastSupper
//
//  Created by Kohei on 2015/07/20.
//
//

#ifndef __SAVE_DATA_SELECTOR_H__
#define __SAVE_DATA_SELECTOR_H__

#include "Layers/baseMenuLayer.h"

class SaveDataSelector : public baseMenuLayer
{
	// クラスメソッド
public:
	CREATE_FUNC(SaveDataSelector);
	virtual bool init();
	
	// クラス変数
private:
	static constexpr float INNER_H_MARGIN_RATIO {0.05f};
	static constexpr float INNER_V_MARGIN_RATIO {0.05f};
	
	// インスタンスメソッド
private:
	void onIndexChanged(bool sound);
	void onSpacePressed();
protected:
	SaveDataSelector();
	~SaveDataSelector();
public:
	void show();
	void hide();
	
	// インスタンス変数
private:
	vector<PlayerDataManager::SaveIndex> saveDatas {};
public:
	function<void(PlayerDataManager::SaveIndex)> onSaveDataSalected { nullptr };
};

#endif // __SAVE_DATA_SELECTOR_H__
