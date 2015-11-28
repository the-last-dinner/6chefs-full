//
//  TitleSceneData.cpp
//  LastSupper
//
//  Created by Kohei on 2015/07/04.
//
//

#include "TitleSceneData.h"

// コンストラクタ
TitleSceneData::TitleSceneData()
{
	FUNCLOG
	this->init();
}

// デストラクタ
TitleSceneData::~TitleSceneData()
{FUNCLOG}

// 初期化
bool TitleSceneData::init()
{
	this->textureFilePaths =
	{
		"title",
		"frame",
        "menu_panels",
        "character/magoichi",
        "character/daigoro",
        "character/dandan",
        "character/nadeshiko",
        "character/manaka",
        "character/ranmaru",
        "character/shituji",
        "character/yuki",
        "character/fujin",
        "character/knife",
        "character/taihou",
        "character/Tfujin",
        "character/wManaka",
        "character/wDandan",
        "character/sRanmaru",
        "character/dDaigoro",
	};
	
	this->soundFilePaths =
	{
		"se/cursorMove.mp3",
		"se/back.mp3",
		"se/gameStart.mp3",
		"se/title-enter.mp3"
	};
	return true;
}