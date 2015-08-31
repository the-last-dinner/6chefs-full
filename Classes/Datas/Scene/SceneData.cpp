//
//  SceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/23.
//
//

#include "Datas/Scene/SceneData.h"

// コンストラクタ
SceneData::SceneData(){FUNCLOG}

// デストラクタ
SceneData::~SceneData(){FUNCLOG}

// リソースのプリロードを実行し、ロード状況をコールバックする
void SceneData::preloadResources(const function<void(float)>& callback)
{
	FUNCLOG
	// リソースの個数を格納
	this->resourceSize = this->textureFilePaths.size() + this->soundFilePaths.size();
	
	if(this->resourceSize == 0){
		// 一つもファイルが存在しない場合、その場でコールバック
		callback(1.0f);
		return;
	}
	
	// コールバック用にパーセントを計算&渡す関数を生成
	function<void()> func = [=](){this->calcPercentage(); callback(this->percentage);};
	
	// 一ファイルのロードが完了するたびに関数を実行
	this->preloadTextureAsync(func);
	this->preloadSoundAsync(func);
	return;
}


// テクスチャアトラス非同期読み込み用、コールバックは完了時ではなく、一ファイルのロード完了毎
void SceneData::preloadTextureAsync(const function<void()>& callback)
{
	FUNCLOG
	for(string filePath : textureFilePaths)
	{
		TextureManager::getInstance()->preloadTexture(filePath, callback);
	}
	return;
	
}

// 音声非同期読み込み用、コールバックは完了時ではなく、一ファイルのロード完了毎
void SceneData::preloadSoundAsync(const function<void()>& callback)
{
	FUNCLOG
	thread th = thread([=](){
		for(string filePath : soundFilePaths)
		{
			SoundManager::getInstance()->preloadSound(filePath);
			callback();
		}
	});
	th.detach();
	return;
}

// パーセントを計算し格納
void SceneData::calcPercentage()
{
	FUNCLOG
	mutex mtx;
	mtx.lock();
	this->loaded++;
	this->percentage = static_cast<float>(this->loaded) / static_cast<float>(this->resourceSize);
	CCLOG("NOW %f PERCENT LOADED!!!", this->percentage * 100);
	mtx.unlock();
	return;
}