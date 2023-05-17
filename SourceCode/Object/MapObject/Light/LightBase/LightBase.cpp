#include "LightBase.h"

// @brief LightBaseコンストラクタ //

LightBase::LightBase()
	:ObjectBase(ObjectTag::Light)
	, lightHandle(-1)
	, lightRange(70.0f)
	, lightAtten2(0.002f)
	, lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
	Load();
}

// @brief LightBaseコンストラクタ //

LightBase::LightBase(VECTOR lightPos)
	:ObjectBase(ObjectTag::Light, lightPos)
	, lightHandle(-1)
	, lightRange(70.0f)
	, lightAtten2(0.002f)
	, lightMatColor{ 1.0f,1.0f,1.0f,1.0f }
{
	Load();
}

// @brief LightBaseデストラクタ //

LightBase::~LightBase()
{
	AssetManager::ReleaseMesh(objHandle);
}

// @brief LightBase読み込み処理 //

void LightBase::Load()
{
	//---モデル読み込み---//
	objHandle = AssetManager::GetMesh("../Assets/Map/Light/Light.mv1");						 //モデル読み込み

	MV1SetPosition(objHandle, objPos);                                                      //モデルの座標設定
	MV1SetScale(objHandle, objScale);                                                       //モデルのサイズ設定
}