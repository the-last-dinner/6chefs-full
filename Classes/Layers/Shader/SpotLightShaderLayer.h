//
//  SpotLightShaderLayer.h
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/20.
//
//

#ifndef _SpotLightShaderLayer__
#define _SpotLightShaderLayer__

#include "Layers/Shader/ShaderLayer.h"

class AmbientLightLayer;
class LightMapLayer;

class SpotLightShaderLayer : public ShaderLayer
{
// 定数
private:
    enum struct UniformType
    {
        U_TEXTURE,
        U_LIGHTMAP,
        AMBIENT_COLOR,
        
        SIZE
    };
    
// インスタンス変数
private:
    AmbientLightLayer* ambientLightLayer { nullptr };
    LightMapLayer* lightMapLayer { nullptr };
    
    RenderTexture* lightMapRendTex { nullptr };
    map<UniformType, GLint> uniformLocations {};
    
// インスタンスメソッド
public:
    SpotLightShaderLayer();   // コンストラクタ
    ~SpotLightShaderLayer();  // デストラクタ
    bool init(const Color3B& ambientLightColor);    // 初期化
    virtual void visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags) override;
};

#endif /* defined(_SpotLightShaderLayer__) */
