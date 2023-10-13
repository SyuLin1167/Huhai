#include "LitLight.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">:シーン名</param>
/// <param name="num">:オブジェクト番号</param>
LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene, num)
    , LIT_MAT_COLOR{ 0.2f,0.2f,0.2f,1.0f }
    , lightDistance(0.0f)
{
    //ライト設定
    SetLightEnableHandle(lightHandle,false);

    //モデル設定
    MV1SetMaterialEmiColor(objHandle, 0, LIT_MAT_COLOR);
}

/// <summary>
/// デストラクタ
/// </summary>
LitLight::~LitLight()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void LitLight::Update(const float deltaTime)
{
    //一定距離近づいたら発光
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < ACTION_RANGE)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
        }
    }


    //パラメーターによる距離減衰
    AttenByParam();
}

/// <summary>
/// 描画処理
/// </summary>
void LitLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}