#include<../Rapidjson/istreamwrapper.h>
#include<../Rapidjson/document.h>
#include<fstream>

#include "LightBase.h"

#include"../../../../Scene/PauseScene/PauseMenu/PauseMenu.h"

LightBase::LightBase()
    :ObjBase(ObjTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.004f)
    , LIGHT_MAT_COLOR{ 1.0f,1.0f,1.0f,1.0f }
{
    //ライト設定
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

LightBase::LightBase(std::string scene,std::string num)
    :ObjBase(ObjTag::Light)
    , lightHandle(-1)
    , lightAtten2(0.008f)
    , LIGHT_MAT_COLOR{ 1.0f,1.0f,1.0f,1.0f }
{
    //ファイル読み込み
    std::ifstream ifs("../SourceCode/Object/MapObject/Light/LightBase/LightData.json");
    rapidjson::Document doc;

    //ファイル解析
    if (ifs.good())
    {
        rapidjson::IStreamWrapper isw(ifs);

        doc.ParseStream(isw);
    }
    ifs.close();

    //データを読み取って座標に代入
    auto& data = doc[scene.c_str()][num.c_str()];
    objPos.x = data["pos"].GetArray()[0].GetFloat();
    objPos.y = LIGHT_POS_Y;
    objPos.z = data["pos"].GetArray()[1].GetFloat();

    //ライト設定
    lightHandle = CreatePointLightHandle(objPos, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);

    //モデル設定
    objPos.y = LIGHTMODEL_POS_Y;
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}

LightBase::~LightBase()
{
    //ライト削除
    DeleteLightHandle(lightHandle);
}

void LightBase::AttenByParam()
{
    float param = MIN_ATTEN_PARAM - (static_cast<float>(PauseMenu::Parameter("Brightness")) / DECIMAL_CONV);
    if (lightAtten2 != param)
    {
        lightAtten2 = param;
        SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);
    }
}