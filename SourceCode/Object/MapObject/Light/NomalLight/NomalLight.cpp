#include "NomalLight.h"

// コンストラクタ //

NomalLight::NomalLight()
    :LightBase()
{
    Load();
}

// コンストラクタ //

NomalLight::NomalLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// デストラクタ //

NomalLight::~NomalLight()
{
    //ライト削除
    DeleteLightHandle(lightHandle);

    //モデル削除
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void NomalLight::Load()
{
    //ライト設定
    SetLightPositionHandle(lightHandle, objPos);

    //モデル設定
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    MV1SetPosition(objHandle, objPos);
}

// 更新処理 //

void NomalLight::Update(float deltaTime)
{
    //座標更新
    SetLightPositionHandle(lightHandle, objPos);
    MV1SetPosition(objHandle, objPos);
}

// 描画処理 //

void NomalLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}