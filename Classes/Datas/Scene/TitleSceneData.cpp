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
	FUNCLOG
	this->textureFilePaths =
	{
		"title",
		"frame"
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