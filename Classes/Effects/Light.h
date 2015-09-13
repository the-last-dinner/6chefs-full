//
//  Light.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/13.
//
//

#ifndef _Light__
#define _Light__

#include "Common.h"

class Light : public Node
{
// 定数
public:
	static const Color3B TORCH_COLOR;
    
// クラスメソッド
public:
	static Light* create(const Color3B& color, float radius);
	CREATE_FUNC_WITH_PARAM(Light, float);
	
// インスタンス変数
private:

// インスタンスメソッド
public:
    Light();   // コンストラクタ
    ~Light();  // デストラクタ
    bool init(const Color3B& color, float radius);    // 初期化
	bool init(float radius);						  // 初期化
};

#endif /* defined(_Light__) */
