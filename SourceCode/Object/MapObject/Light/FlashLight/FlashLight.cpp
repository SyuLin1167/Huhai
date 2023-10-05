#include "FlashLight.h"

// コンストラクタ //

FlashLight::FlashLight()
    :LightBase()
{
    //ライト設定
    DeleteLightHandle(lightHandle);
    lightHandle = CreateSpotLightHandle(objPos, objDir,
        DX_PI_F / 4.0f, DX_PI_F / 8.0f, LIGHT_RANGE, 0.0f, 0.0f, 0.0f);

    isVisible = false;
}

// デストラクタ //

FlashLight::~FlashLight()
{
    //ライト削除
    DeleteLightHandle(lightHandle);
}

// 読み込み処理 //

void FlashLight::Load()
{
    //処理なし
}

// 更新処理 //

void FlashLight::Update(float deltaTime)
{
    //カメラの方向にライトを当てる
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    SetLightDirectionHandle(lightHandle, camera->GetDir());


    //パラメーターによる距離減衰
    AttenByParam();
}

// 描画処理 //

void FlashLight::Draw()
{
}