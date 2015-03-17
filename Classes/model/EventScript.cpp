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
}

// デストラクタ
EventScript::~EventScript()
{
}

//イベントスクリプトファイルの読み込み
void readScript ()
{
    ifstream filein("TestScript.txt");
    
    for (string line; getline(filein, line); )
    {
        cout << line << endl;
    }
    return;
}