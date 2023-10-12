#include "LitLight.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">:シーン名</param>
/// <param name="num">:オブジェクト番号</param>
LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , lightDistance(0.0f)
{
    //ライト設定
    SetLightEnableHandle(lightHandle,false);
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
/// <param name="deltaTime">:フレームレート</param>
void LitLight::Update(float deltaTime)
{
    //一定距離近づいたら発光
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < ACTION_RANGE)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
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