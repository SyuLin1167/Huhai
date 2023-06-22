#include "LightBase.h"

// コンストラクタ //

LightBase::LightBase()
    :ObjBase(ObjectTag::Light)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// コンストラクタ //

LightBase::LightBase(VECTOR pos)
    :ObjBase(ObjectTag::Light, pos)
    , lightHandle(-1)
    , lightRange(70.0f)
    , lightAtten2(0.002f)
    , lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
    Load();
}

// デストラクタ //

LightBase::~LightBase()
{
    //モデル削除
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void LightBase::Load()
{
    //モデル設定
    objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");
    MV1SetPosition(objHandle, objPos);
    MV1SetScale(objHandle, objScale);
}