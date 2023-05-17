#include "LitLight.h"

// @brief LitLightコンストラクタ //

LitLight::LitLight()
    :LightBase()
    ,lightDistance(0.0f)
{
    Load();
}

// @brief LitLightコンストラクタ //

LitLight::LitLight(VECTOR lightPos, float range)
    :LightBase(lightPos)
    , lightDistance(0.0f)
    , actionRange(range)
{
    Load();
}

// @brief LitLightデストラクタ //

LitLight::~LitLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

// @brief LitLight読み込み処理 //

void LitLight::Load()
{    
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    SetLightEnableHandle(lightHandle, FALSE);
}

// @brief LitLight更新処理 //

void LitLight::Update(float deltaTime)
{
    //---オブジェクトの中身判定---//
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);        //プレイヤーオブジェクト取得
    if (player)
    {
        //---ライトの点灯処理---//
        lightDistance = VSize(player->GetPos() - objPos);                       //プレイヤーとライトとの距離取得

        if (abs(lightDistance) < actionRange)                                         //一定距離近づいたら
        {
            SetLightEnableHandle(lightHandle, TRUE);
            lightMatColor = { 1.0f,1.0f,1.0f,1.0f };                            //輝度を明るく発光色を白にする
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);                    //輝度と発光色設定
        }
    }
}

// @brief LitLight描画処理 //

void LitLight::Draw()
{
    MV1DrawModel(objHandle);                                                //モデル描画
}