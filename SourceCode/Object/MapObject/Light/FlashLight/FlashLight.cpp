#include "FlashLight.h"

// コンストラクタ //

FlashLight::FlashLight()
    :LightBase()
{
    Load();
}

// コンストラクタ //

FlashLight::FlashLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// デストラクタ //

FlashLight::~FlashLight()
{
    //ライト削除
    DeleteLightHandle(lightHandle);

    //モデル削除
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void FlashLight::Load()
{
    //ライト設定
    lightAtten2 = 0.0005f;
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2 * 10);
}

// 更新処理 //

void FlashLight::Update(float deltaTime)
{
    //プレイヤーの周辺を光らせる
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    //SetLightDirectionHandle(lightHandle, camera->GetDir());
}

// 描画処理 //

void FlashLight::Draw()
{
}