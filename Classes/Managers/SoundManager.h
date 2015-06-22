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

public:
	~SoundManager();
	void setBasePath(const string& seBasePath, const string& bgmBasePath);
	void preloadBGM(const string& fileName);
	void preloadSE(const string& fileName);
	void playBGM(const string& fileName, bool loop = false);
	void playSE(const string& fileName, bool loop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
	void unloadSounds();
	
	// インスタンス変数
private:
	string seBasePath;
	string bgmBasePath;
	vector<string> soundList;
};

#endif // __SOUND_MANAGER_H__
