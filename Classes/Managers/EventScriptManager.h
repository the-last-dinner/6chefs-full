//
//  EventScript.h
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#ifndef __LastSupper__EventScriptManager__
#define __LastSupper__EventScriptManager__

#include "define.h"

class EventScriptManager
{
public:
    //あとで使うかもしれないメモの構造体
    enum struct EventType
    {
        PlaySE,
        Fade,
        Move,
        Talk,
        Control,
        Message,
        ChangeMap,
        Read,
        Delay,
        //指示系
        SameTime,
        If,
        Sequence,
    };
    //インスタンス用関数(singleton仕様)
    static EventScriptManager* getInstance();
    static void destroy();
    ~EventScriptManager();
    //EventScriptManager関数
    bool setJsonScript(string script);
    std::string trim(const std::string& string, const char* trimCharacterList);
private:
    //インスタンス変数
    Document json;
    //インスタンス用関数(singleton仕様)
    EventScriptManager();                                               // コンストラクタ
    EventScriptManager(const EventScriptManager& other);                // コピーコンストラクタ
    EventScriptManager& operator = (const EventScriptManager& other);   // 代入演算子
    //cocos2dファイル操作用
    cocos2d::FileUtils * fu;
};
#endif /* defined(__LastSupper__EventScript__) */
