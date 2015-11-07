//
//  SoundManager.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/22.
//
//

#include "Managers/SoundManager.h"

// 定数
const string SoundManager::bgmPath = "bgm/";
const string SoundManager::sePath = "se/";

// 唯一のインスタンスを初期化
static SoundManager* _instance = nullptr;

// 唯一のインスタンスを取得
SoundManager* SoundManager::getInstance()
{
	if(!_instance) _instance = new SoundManager();
	return _instance;
}

// インスタンスを破棄
void SoundManager::destory()
{
	delete _instance;
	return;
}

// コンストラクタ
SoundManager::SoundManager()
{FUNCLOG}

// デストラクタ
SoundManager::~SoundManager()
{FUNCLOG}

// 音声ファイルをプリロード
void SoundManager::preloadSound(const string& filePath)
{
	// プリロード関数がないため、音量ゼロで再生する
	int audioId = AudioEngine::play2d(filePath, false, 0.0f);
	this->soundMap.insert({filePath, audioId});
	
	// すぐに再生停止
	AudioEngine::stop(audioId);
	return;
}

// 音声を再生
void SoundManager::playSound(const string& filePath, bool loop, float volume)
{
	AudioEngine::play2d(filePath, loop, volume);
	return;
}

// 音声をアンロード
void SoundManager::unloadAllSounds()
{
	FUNCLOG
	// 音声パスリストを元にアンロードしていく
	for(auto iterator : this->soundMap)
	{
		AudioEngine::uncache(iterator.first);
	}
	
	// 音声パスリストを初期化する
	this->soundMap.clear();
	return;
}