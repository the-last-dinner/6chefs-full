//
//  SceneData.h
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#ifndef __SCENE_DATA_H__
#define __SCENE_DATA_H__

#include "Common.h"

class SceneData : public Ref
{
	// インスタンスメソッド
public:
	void preloadResources(const function<void(float)>& callback);
protected:
	SceneData();
	~SceneData();
private:
	void calcPercentage();
	void preloadTextureAsync(const function<void()>& callback);
	void preloadSoundAsync(const function<void()>& callback);
	
	// インスタンス変数
protected:
	vector<string> textureFilePaths {};
	vector<string> soundFilePaths {};
private:
	float percentage {0};	// リソースのロード状況（1.0fで100%）
	int loaded {0};
	int resourceSize {0};
};

#endif // __SCENE_DATA_H__
