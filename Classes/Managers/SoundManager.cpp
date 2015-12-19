//
//  SoundManager.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/22.
//
//

#include "Managers/SoundManager.h"
#include "Managers/PlayerDataManager.h"
#include "Models/GlobalPlayerData.h"

// 定数
const map<string, float> SoundManager::VOLUME_CONFIG
{
    {Resource::SE::CURSOR_MOVE, 0.5f},
    {Resource::SE::BACK, 0.5f},
    {Resource::SE::TITLE_ENTER, 0.5f},
};

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
    _instance = nullptr;
}

// コンストラクタ
SoundManager::SoundManager()
{FUNCLOG}

// デストラクタ
SoundManager::~SoundManager()
{FUNCLOG}

// SEを再生
void SoundManager::playSE(const string& fileName, float volume)
{
    if(VOLUME_CONFIG.count(fileName) != 0) volume *= VOLUME_CONFIG.at(fileName);
    AudioEngine::play2d(Resource::SE::BASE_PATH + fileName, false, volume * PlayerDataManager::getInstance()->getGlobalData()->getSeVolume());
}

// BGMを再生
void SoundManager::playBGM(const string& fileName, bool loop, float volume)
{
    if(VOLUME_CONFIG.count(fileName) != 0) volume *= VOLUME_CONFIG.at(fileName);
    int BGMId { AudioEngine::play2d(Resource::BGM::BASE_PATH + fileName, loop, volume * PlayerDataManager::getInstance()->getGlobalData()->getBgmVolume()) };
    
    this->bgmIdMap.insert({BGMId, fileName});
}

// BGMをファイル名指定で停止
void SoundManager::stopBGM(const string& filePath)
{
    for(pair<int, string> idToPath : this->bgmIdMap)
    {
        if(idToPath.second == filePath) AudioEngine::stop(idToPath.first);
    }
}

// BGM全て停止
void SoundManager::stopBGMAll()
{
    if(this->bgmIdMap.empty()) return;
    
    for(pair<int, string> idToPath : this->bgmIdMap)
    {
        AudioEngine::stop(idToPath.first);
    }
}

// 音声ファイルをプリロード
void SoundManager::preloadSound(const string& filePath)
{
    // プリロード関数がないため、音量ゼロで再生する
    int audioId { AudioEngine::play2d(filePath, false, 0.0f) };
    this->preloadMap.insert({audioId, filePath});
    
    // すぐに再生停止
    AudioEngine::stop(audioId);
}

// 音声をアンロード
void SoundManager::unloadAllSounds()
{
	FUNCLOG
	// 音声パスリストを元にアンロードしていく
	for(auto iterator : this->preloadMap)
	{
		AudioEngine::uncache(iterator.second);
	}
	
	// 音声パスリストを初期化する
	this->preloadMap.clear();
}