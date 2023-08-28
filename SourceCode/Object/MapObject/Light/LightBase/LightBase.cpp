#include "LightBase.h"

#include"../../../../Scene/PauseMenu/PauseMenu.h"

// コンストラクタ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.004f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// コンストラクタ //

LightBase::LightBase(VECTOR pos)
    :ObjBase(ObjectTag::Light, pos)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.004f)
    , lightMatColor(GetColorF(1.0f, 1.0f, 1.0f, 1.0f))
{
    Load();
}

// デストラクタ //

LightBase::~LightBase()
{
    //ライト削除
    DeleteLightHandle(lightHandle);
}

// 読み込み処理 //

void LightBase::Load()
{
    //ライト設定
    lightHandle = CreatePointLightHandle(objPos + VGet(0.0f, 2.5f, 0.0f) , lightRange, 0.0f, 0.0f, lightAtten2 * 2.0f);

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

// パラメータによる距離減衰 //

void LightBase::AttenByParam()
{
    float param = 0.01f - (static_cast<float>(PauseMenu::Parameter("Brightness")) / 10000.0f);
    if (lightAtten2 != param)
    {
        lightAtten2 = param;
        SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);
    }
}