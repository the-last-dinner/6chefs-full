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

class SceneData
{
	// インスタンスメソッド
public:
	SceneData();
	~SceneData();
	void preloadResources(const function<void(float)>& callback);
	void unloadAllFiles();
private:
	void calcPercentage();
	void preloadTextureAsync(const function<void()>& callback);
	void preloadSoundAsync(const function<void()>& callback);
	
	// インスタンス変数
protected:
	vector<string> textureFilePaths;
	vector<string> soundFilePaths;
private:
	float percentage;	// リソースのロード状況（1.0fで100%）
	int loaded;
	int resourceSize;
};

#endif // __SCENE_DATA_H__
