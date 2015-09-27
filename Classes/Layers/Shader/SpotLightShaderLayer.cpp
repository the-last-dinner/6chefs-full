//
//  SpotLightShaderLayer.cpp
//  LastSupper
//
//  Created by Kohei Asami on 2015/09/20.
//
//

#include "Layers/Shader/SpotLightShaderLayer.h"

#include "Effects/AmbientLightLayer.h"

// コンストラクタ
SpotLightShaderLayer::SpotLightShaderLayer() { FUNCLOG }

// デストラクタ
SpotLightShaderLayer::~SpotLightShaderLayer()
{
    FUNCLOG
    CC_SAFE_RELEASE_NULL(this->ambientLightLayer);
    CC_SAFE_RELEASE_NULL(this->lightMapLayer);
}

// 初期化
bool SpotLightShaderLayer::init(const Color3B& ambientLightColor)
{
    if(!ShaderLayer::init("shaders/spotlight.vert", "shaders/spotlight.frag")) return false;
    
    // 環境光レイヤー生成
    AmbientLightLayer* ambientLightLayer {AmbientLightLayer::create(ambientLightColor)};
    this->ambientLightLayer = ambientLightLayer;
    CC_SAFE_RETAIN(ambientLightLayer);
    
    // 光の分布レイヤー生成
    LightMapLayer* lightMapLayer { LightMapLayer::create() };
    this->lightMapLayer = lightMapLayer;
    CC_SAFE_RETAIN(lightMapLayer);
    
    // 光の分布用のレンダーテクスチャ生成
    RenderTexture* renderTexture {RenderTexture::create(Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height)};
    this->lightMapRendTex = renderTexture;
    CC_SAFE_RETAIN(renderTexture);
    
    this->uniformLocations[UniformType::U_TEXTURE] = glGetUniformLocation(this->glProgram->getProgram(), "u_texture");
    //this->uniformLocations[UniformType::U_LIGHTMAP] = glGetUniformLocation(this->glProgram->getProgram(), "u_lightmap");
    this->uniformLocations[UniformType::AMBIENT_COLOR] = glGetUniformLocation(this->glProgram->getProgram(), "ambientColor");
    
    return true;
}

void SpotLightShaderLayer::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    ShaderLayer::visit(renderer, parentTransform, parentFlags);
    
    this->lightMapRendTex->beginWithClear(0, 0, 0, 0);
    this->lightMapLayer->visit();
    this->lightMapRendTex->end();
    
    this->glProgram->use();
    this->glProgram->setUniformsForBuiltins();
    
    this->glProgramState->setUniformTexture(this->uniformLocations[UniformType::U_TEXTURE], this->renderTexture->getSprite()->getTexture()->getName());
    //this->glProgramState->setUniformTexture(this->uniformLocations[UniformType::U_LIGHTMAP], this->lightMapRendTex->getSprite()->getTexture()->getName());
    
    Color4F ambientColor {this->ambientLightLayer->getColor()};
    this->glProgramState->setUniformVec4(this->uniformLocations[UniformType::AMBIENT_COLOR], Vec4(ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a));
}