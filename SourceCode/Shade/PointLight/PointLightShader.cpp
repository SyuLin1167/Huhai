#include "PointLightShader.h"
#include<DxLib.h>

/// <summary>
/// コンストラクタ
/// </summary>
PointLightShader::PointLightShader()
{
    //シェーダー読み込み
    VSHandle = LoadVertexShader("../SourceCode/Shade/PointLight/PointLightVS.vso");
    PSHandle = LoadPixelShader("../SourceCode/Shade/PointLight/PointLightPS.pso");

    //シェーダー設定
    MV1SetUseOrigShader(true);
    SetUseVertexShader(VSHandle);
    SetUsePixelShader(PSHandle);
}

/// <summary>
/// デストラクタ
/// </summary>
PointLightShader::~PointLightShader()
{
    //シェーダーの後処理
    DeleteShader(VSHandle);
    DeleteShader(PSHandle);
}