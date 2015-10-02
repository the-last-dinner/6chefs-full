#ifndef  __DEFINE_H__
#define  __DEFINE_H__

// Common.hにインクルードされるファイル群(Manager系)はこちらをインクルードする
// 最低限のインクルード、変数の初期化を行う

#include <cocos2d.h>
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include <iostream>
#include <fstream>
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"

// ゲームウインドウ横幅、縦幅
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// 1マスの大きさ(px)
#define GRID 16

// DEBUGモードの時はdefineしておく
#define DEBUG

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;
using namespace rapidjson;
using namespace experimental;

// メソッドログ
#ifdef DEBUG
#define FUNCLOG CCLOG("%s::%s", typeid(*this).name(), __FUNCTION__);
#else
#define FUNCLOG
#endif

// 画面の中心点
#define WINDOW_CENTER Point(WINDOW_WIDTH, WINDOW_HEIGHT) / 2

// レイヤーのZORDER値
enum Priority
{
	SCREEN_COVER = 999,
	STORY_MESSAGE = 102,
	SYSTEM_MESSAGE = 101,
    CHARACTER_MESSAGE = 100,
    DEBUG_MASK = 70,
    AMBIENT_LIGHT = 50,
	MAP = 0,
};

// ゲームで使うキーの種類
enum struct Key
{
    DOWN,
    RIGHT,
    LEFT,
    UP,
    MENU,
    DASH,
    SPACE,
    
    SIZE,
};

// 向き
enum struct Direction
{
	FRONT,
	RIGHT,
	LEFT,
	BACK,
	SIZE,
};

// トリガータイプ
enum struct Trigger
{
	INIT,
	RIDE,
	SEARCH,
	SIZE,
	NONE,
};

// パラメータを一つタイプを指定してcreate
#define CREATE_FUNC_WITH_PARAM(__TYPE_1__, __TYPE_2__) \
static __TYPE_1__* create(__TYPE_2__ param) \
{ \
	__TYPE_1__ *pRet = new(std::nothrow) __TYPE_1__(); \
	if (pRet && pRet->init(param)) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
}

#endif // __DEFINE_H__