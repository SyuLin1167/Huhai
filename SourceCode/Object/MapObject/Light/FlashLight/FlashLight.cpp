#include "FlashLight.h"

        // コンストラクタ //

FlashLight::FlashLight()
    :LightBase()
{
    Load();
}

        // コンストラクタ //

FlashLight::FlashLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // デストラクタ //

FlashLight::~FlashLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

        // 読み込み処理 //

void FlashLight::Load()
{
    lightAtten2 = 0.0005f;
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2 * 10);
}

        // 更新処理 //

void FlashLight::Update(float deltaTime)
{
    ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    //SetLightDirectionHandle(lightHandle, camera->GetDir());
}

        // 描画処理 //

void FlashLight::Draw()
{
}