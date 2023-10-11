#include "LitLight.h"

// コンストラクタ //

LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , lightDistance(0.0f)
{
    //ライト設定
    SetLightEnableHandle(lightHandle,false);
}

// デストラクタ //

LitLight::~LitLight()
{
    //処理なし
}

// 更新処理 //

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

// 描画処理 //

void LitLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}