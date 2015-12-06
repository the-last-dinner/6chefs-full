//
//  SoundManager.h
//  LastSupper
//
//  Created by Kohei on 2015/06/22.
//
//

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "define.h"

class SoundManager
{
// クラスメソッド
public:
	static SoundManager* getInstance();
	static void destory();
	
// シングルトンであるためにprivateに
private:
	SoundManager();												// コンストラクタ
	SoundManager(const SoundManager& other);					// デストラクタ
	SoundManager& operator = (const SoundManager& other);		// 代入演算子
	~SoundManager();											// デストラクタ

public:
    void playSE(const string& filePath, float volume = 1.f);
    void playBGM(const string& filePath, bool loop = true, float volume = 1.f);
    
    void stopBGM(const string& filePath);
    void stopBGMAll();
    
    void preloadSound(const string& filePath);
	void unloadAllSounds();
	
	// インスタンス変数
private:
    map<int, string> preloadMap {};
    map<int, string> bgmIdMap {};
};

#endif // __SOUND_MANAGER_H__
