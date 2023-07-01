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
    //モデル設定
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    MV1SetPosition(objHandle, objPos);
}

// 更新処理 //

void NomalLight::Update(float deltaTime)
{
    //座標更新
    SetLightPositionHandle(lightHandle, objPos + VGet(0.0f, 2.5f, 0.0f));
    MV1SetPosition(objHandle, objPos);
}

// 描画処理 //

void NomalLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}