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
enum struct Priority
{
	SCREEN_EFFECT = 100,
	CHARACTER_MESSAGE = 50,
	SYSTEM_MESSAGE = 60,
	MAP = 0,
};

// 向き
enum struct Direction
{
	FRONT,
	RIGHT,
	LEFT,
	BACK,
	SIZE,
	FRONT_RIGHT,
	FRONT_LEFT,
	BACK_RIGHT,
	BACK_LEFT,
	NONE,
};

// トリガータイプ
enum struct TriggerType
{
	INIT,
	RIDE,
	SEARCH,
	SIZE,
	NONE,
};

// 向きと移動量を結びつける連想配列
const map<Direction, Point> movementMap =
{
	{Direction::FRONT, Point(0, -GRID)},
	{Direction::RIGHT, Point(GRID, 0)},
	{Direction::LEFT, Point(-GRID, 0)},
	{Direction::BACK, Point(0, GRID)},
	{Direction::FRONT_RIGHT, Point(GRID, -GRID)},
	{Direction::FRONT_LEFT, Point(-GRID, -GRID)},
	{Direction::BACK_RIGHT, Point(GRID, GRID)},
	{Direction::BACK_LEFT, Point(-GRID, GRID)},
};

// stringを用いて初期化、メッセージレイヤー系
#define CREATE_FUNC_WITH_STR(__TYPE__) \
static __TYPE__* create(const string& str) \
{ \
	__TYPE__ *pRet = new(std::nothrow) __TYPE__(); \
	if (pRet && pRet->init(str)) \
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