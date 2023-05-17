#include "NomalLight.h"

// @brief NomalLightコンストラクタ //

NomalLight::NomalLight()
	:LightBase()
{
	Load();
}

// @brief NomalLightコンストラクタ //

NomalLight::NomalLight(VECTOR lightPos)
	:LightBase(lightPos)
{
	Load();
}

// @brief NomalLightデストラクタ //

NomalLight::~NomalLight()
{
	DeleteLightHandle(lightHandle);
	AssetManager::ReleaseMesh(objHandle);
}

// @brief NomalLight読み込み処理 //

void NomalLight::Load()
{
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// @brief NomalLight更新処理 //

void NomalLight::Update(float deltaTime)
{
	DeleteLightHandle(lightHandle);
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetPosition(objHandle, objPos);
}


// @brief NomalLight描画処理 //

void NomalLight::Draw()
{
	MV1DrawModel(objHandle);						//モデル描画
}