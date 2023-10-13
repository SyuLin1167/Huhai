#include "NomalLight.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">:シーン名</param>
/// <param name="num">:オブジェクト番号</param>
NomalLight::NomalLight(std::string scene, std::string num)
    :LightBase(scene,num)
{
}

/// <summary>
/// デストラクタ
/// </summary>
NomalLight::~NomalLight()
{
    //処理なし
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void NomalLight::Update(float deltaTime)
{
    //パラメーターによる距離減衰
    AttenByParam();
}

/// <summary>
/// 描画処理
/// </summary>
void NomalLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}