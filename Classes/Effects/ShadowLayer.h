//
//  ShadowLayer.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/10.
//
//

#ifndef _ShadowLayer__
#define _ShadowLayer__

#include "Common.h"

class ShadowLayer : public Layer
{
// クラスメソッド
public:
	CREATE_FUNC_WITH_PARAM(ShadowLayer, const Color4B&)

// インスタンスメソッド
private:
    ShadowLayer();   // コンストラクタ
    ~ShadowLayer();  // デストラクタ
    bool init(const Color4B& color);    // 初期化
};

#endif /* defined(_ShadowLayer__) */
