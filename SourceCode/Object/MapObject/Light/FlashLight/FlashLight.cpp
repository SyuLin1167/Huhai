#include "FlashLight.h"

/// <summary>
/// コンストラクタ
/// </summary>
FlashLight::FlashLight()
    :LightBase()
{
    //ライト設定
    DeleteLightHandle(lightHandle);
    lightHandle = CreateSpotLightHandle(objPos, objDir,
        DX_PI_F / 4.0f, DX_PI_F / 8.0f, LIGHT_RANGE, 0.0f, 0.0f, 0.0f);

    isVisible = false;
}

/// <summary>
/// デストラクタ
/// </summary>
FlashLight::~FlashLight()
{
    //ライト削除
    DeleteLightHandle(lightHandle);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void FlashLight::Update(const float deltaTime)
{
    //カメラの方向にライトを当てる
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    SetLightDirectionHandle(lightHandle, camera->GetDir());


    //パラメーターによる距離減衰
    AttenByParam();
}

/// <summary>
/// 描画処理
/// </summary>
void FlashLight::Draw()
{
    //処理なし
}