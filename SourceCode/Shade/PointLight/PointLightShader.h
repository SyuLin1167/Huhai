#pragma once

/// <summary>
/// ポイントライトのシェーダー
/// </summary>
class PointLightShader
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PointLightShader();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PointLightShader();

private:
    int VSHandle;       //頂点シェーダーハンドル
    int PSHandle;       //ピクセルシェーダーハンドル

};

