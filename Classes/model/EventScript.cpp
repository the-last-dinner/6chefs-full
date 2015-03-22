//
//  EventScript.cpp
//  LastSupper
//
//  Created by 猪野凌也 on 2015/03/15.
//
//

#include "EventScript.h"

using namespace std;

// コンストラクタ
EventScript::EventScript()
{
    cout<<"EventScriptのコンストラクタが呼び出されました。";
}

// デストラクタ
EventScript::~EventScript()
{
    cout<<"EventScriptのコンストラクタが呼び出されました。";
}

//イベントスクリプトファイルの読み込み
void EventScript::readScript ()
{
    string path = "/Users/Ryoya/Source/Xcode/LastSupper/Resources/TestScript.txt";
    //string path = "TestScript.txt";
    ifstream filein(path);
    cout << "bbb";
    for (string line; getline(filein, line); )
    {
        cout << line << endl;
    }
    return;
}