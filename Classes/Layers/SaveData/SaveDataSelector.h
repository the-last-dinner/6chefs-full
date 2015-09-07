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
	virtual void onIndexChanged(bool sound);
	virtual void onSpacePressed();
	virtual void onMenuKeyPressed();
protected:
	SaveDataSelector();
	~SaveDataSelector();
public:
	virtual void show() override;
	virtual void hide() override;
	
	// インスタンス変数
private:
	vector<PlayerDataManager::SaveIndex> saveDatas {};
public:
	function<void(int)> onSaveDataSalected { nullptr };
	function<void()> onSaveDataSelectCancelled { nullptr };
};

#endif // __SAVE_DATA_SELECTOR_H__
