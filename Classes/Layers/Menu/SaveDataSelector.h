//
//  SaveDataSelector.h
//  LastSupper
//
//  Created by Kohei on 2015/07/20.
//
//

#ifndef __SAVE_DATA_SELECTOR_H__
#define __SAVE_DATA_SELECTOR_H__

#include "Layers/Menu/MenuLayer.h"

class SaveDataSelector : public MenuLayer
{
	// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(SaveDataSelector, bool);
	virtual bool init(bool write);
	
	// クラス変数
private:
	static constexpr float INNER_H_MARGIN_RATIO {0.05f};
	static constexpr float INNER_V_MARGIN_RATIO {0.05f};
	
	// インスタンスメソッド
private:
	virtual void onIndexChanged(int newIdx, bool sound);
	virtual void onSpacePressed(int idx);
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
    bool write_flag;
    bool comfirm_flag;
public:
	function<void(int)> onSaveDataSelected { nullptr };
	function<void()> onSaveDataSelectCancelled { nullptr };
};

#endif // __SAVE_DATA_SELECTOR_H__
