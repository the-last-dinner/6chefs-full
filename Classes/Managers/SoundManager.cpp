//
//  SoundManager.cpp
//  LastSupper
//
//  Created by Kohei on 2015/06/22.
//
//

#include "SoundManager.h"

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

// サウンドファイルが存在するディレクトリルートを指定
void SoundManager::setBasePath(const string& seBasePath, const string& bgmBasePath)
{
	FUNCLOG
	this->seBasePath = seBasePath;
	this->bgmBasePath = bgmBasePath;
	return;
}

// BGMファイルをプリロード
void SoundManager::preloadBGM(const string& fileName)
{
	FUNCLOG
	this->soundList.push_back(fileName);
	SimpleAudioEngine::getInstance()->preloadEffect((this->bgmBasePath + fileName).c_str());
	return;
}

// SEファイルをプリロード
void SoundManager::preloadSE(const string& fileName)
{
	FUNCLOG
	this->soundList.push_back(fileName);
	SimpleAudioEngine::getInstance()->preloadEffect((this->seBasePath + fileName).c_str());
	return;
}

// BGMを再生（内部処理はSEと同じだが無駄な引数入力を省略させるため）
void SoundManager::playBGM(const string& fileName, bool loop)
{
	FUNCLOG
	SimpleAudioEngine::getInstance()->playEffect((this->bgmBasePath + fileName).c_str(), loop);
	return;
}

// SEを再生
void SoundManager::playSE(const string& fileName, bool loop, float pitch, float pan, float gain)
{
	FUNCLOG
	SimpleAudioEngine::getInstance()->playEffect((this->seBasePath + fileName).c_str(), loop, pitch, pan, gain);
	return;
}

// 音声ファイルをアンロード
void SoundManager::unloadSounds()
{
	FUNCLOG
	int count = this->soundList.size();
	
	// リストに何も登録されていなかったらlog出力
	if(count == 0)
	{
		log("音声ファイルがありません！！");
		return;
	}
	
	// 音声ファイル名リストを元にアンロードしていく
	for(int i = 0; i < count; i++)
	{
		SimpleAudioEngine::getInstance()->unloadEffect(this->soundList.at(i).c_str());
	}
	
	// 音声ファイル名リストを初期化する
	this->soundList.clear();
	return;
}