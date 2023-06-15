#include "NomalLight.h"

        // コンストラクタ //

NomalLight::NomalLight()
    :LightBase()
{
    Load();
}

        // コンストラクタ //

NomalLight::NomalLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // デストラクタ //

NomalLight::~NomalLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

        // @brief NomalLight読み込み処理 //

void NomalLight::Load()
{
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

        // @brief NomalLight更新処理 //

void NomalLight::Update(float deltaTime)
{
    SetLightPositionHandle(lightHandle, objPos);
    MV1SetPosition(objHandle, objPos);
}

        // @brief NomalLight描画処理 //

void NomalLight::Draw()
{
    MV1DrawModel(objHandle);						//モデル描画
}