#include "LitLight.h"

// コンストラクタ //

LitLight::LitLight(VECTOR pos, float range)
    :LightBase(pos)
    , lightDistance(0.0f)
    , actionRange(range)
{
    Load();
}

// デストラクタ //

LitLight::~LitLight()
{
    //ライト削除
    DeleteLightHandle(lightHandle);

    //モデル削除
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void LitLight::Load()
{

    SetLightEnableHandle(lightHandle,FALSE);
}

        // 更新処理 //

void LitLight::Update(float deltaTime)
{
    //一定距離近づいたら発光
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < actionRange)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            lightMatColor = { 1.0f,1.0f,1.0f,1.0f };
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
        }
    }
}

// 描画処理 //

void LitLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}