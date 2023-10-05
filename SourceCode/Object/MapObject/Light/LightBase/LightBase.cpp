#include "LightBase.h"

#include"../../../../Scene/PauseMenu/PauseMenu.h"

// コンストラクタ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.008f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    //ライト設定
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");

    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

// コンストラクタ //

LightBase::LightBase(std::string scene,std::string num)
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.008f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    //ファイル読み込み
    LoadJsonFile("LightData.json");
    auto& data = doc[scene.c_str()][num.c_str()];
    objPos.x = data["pos"].GetArray()[0].GetInt();
    objPos.y = LIGHT_POS_Y;
    objPos.z = data["pos"].GetArray()[2].GetInt();

    //ライト設定
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");

    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

// デストラクタ //

LightBase::~LightBase()
{
    //ライト削除
    DeleteLightHandle(lightHandle);
}

// パラメータによる距離減衰 //

void LightBase::AttenByParam()
{
    float param = MIN_ATTEN_PARAM - (static_cast<float>(PauseMenu::Parameter("Brightness")) / 10000.0f);
    if (lightAtten2 != param)
    {
        lightAtten2 = param;
        SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);
    }
}