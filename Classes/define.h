#ifndef  __DEFINE_H__
#define  __DEFINE_H__

// Common.hにインクルードされるファイル群(Manager系)はこちらをインクルードする
// 最低限のインクルード、変数の初期化を行う

#include <cocos2d.h>
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"
#include <iostream>
#include <fstream>

// rapidjson
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;
typedef GenericDocument< UTF8<> > Document;
typedef GenericValue< UTF8<> > Value;
typedef GenericStringStream< UTF8<> > StringStream;
typedef GenericStringBuffer< UTF8<> > StringBuffer;

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
using namespace experimental;

// メソッドログ
#ifdef DEBUG
#define FUNCLOG CCLOG("%s::%s", typeid(*this).name(), __FUNCTION__);
#else
#define FUNCLOG
#endif

// 画面の中心点
#define WINDOW_CENTER Point(WINDOW_WIDTH, WINDOW_HEIGHT) / 2

// セーブデータの個数
#define MAX_SAVE_COUNT 10

// レイヤーのZORDER値
enum Priority
{
    LOADING_LAYER = 999,
	STORY_MESSAGE = 102,
	SYSTEM_MESSAGE = 101,
    CHARACTER_MESSAGE = 100,
    SELECT_LAYER = 92,
    BUTTON_MASHING_LAYER = 91,
    DISP_IMAGE_LAYER = 90,
    SCREEN_COVER = 80,
    DEBUG_MASK = 40,
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
    AFTER_INIT,
	SIZE,
};

// オブジェクトID
enum struct ObjectID
{
    UNDIFINED = -1,
};

// イベントID
enum struct EventID
{
    UNDIFINED = -1,
};

// キャラクターID
enum struct CharacterID
{
    UNDIFINED = -1,
};

// 味方キャラクタの動き方
enum struct CharacterMovePattern
{
    NONE = 1,
    RANDOM = 2,
    
    SIZE,
};

// 敵キャラクタの動き方
enum struct EnemyMovePattern
{
    CHASE,
    RANDOM,
    SPEED_UP,
    PERFECT_RANDOM,
    SERCH,
    PERFECT_CHASE,
    
    SIZE,
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

#define CREATE_FUNC_WITH_TWO_PARAM(__TYPE_1__, __TYPE_2__, __TYPE_3__) \
static __TYPE_1__* create(__TYPE_2__ param1, __TYPE_3__ param2) \
{ \
    __TYPE_1__ *pRet = new(std::nothrow) __TYPE_1__(); \
    if (pRet && pRet->init(param1, param2)) \
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