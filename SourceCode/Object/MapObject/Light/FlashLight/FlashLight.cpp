#include "FlashLight.h"

// @brief FlashLightコンストラクタ //

FlashLight::FlashLight()
	:LightBase()
{
	Load();
}

// @brief FlashLightコンストラクタ //

FlashLight::FlashLight(VECTOR lightPos)
	:LightBase(lightPos)
{
	Load();
}

// @brief FlashLightデストラクタ //

FlashLight::~FlashLight()
{
	DeleteLightHandle(lightHandle);
	AssetManager::ReleaseMesh(objHandle);
}

// @brief FlashLight読み込み処理 //

void FlashLight::Load()
{
	lightAtten2 = 0.0005f;
	/*lightHandle = CreateSpotLightHandle(objPos, objDir,
		DX_PI_F / 6.0f, DX_PI_F / 4.0f, lightRange, 0.0f, 0.0f, lightAtten2);*/
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2 * 10);
}

// @brief FlashLight更新処理 //

void FlashLight::Update(float deltaTime)
{
	ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
	SetLightPositionHandle(lightHandle, camera->GetPos());
	//SetLightDirectionHandle(lightHandle, camera->GetDir());
}

// @brief FlashLight描画処理 //

void FlashLight::Draw()
{
}