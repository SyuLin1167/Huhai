#include "FlashLight.h"

// @brief FlashLight�R���X�g���N�^ //

FlashLight::FlashLight()
	:LightBase()
{
	Load();
}

// @brief FlashLight�R���X�g���N�^ //

FlashLight::FlashLight(VECTOR lightPos)
	:LightBase(lightPos)
{
	Load();
}

// @brief FlashLight�f�X�g���N�^ //

FlashLight::~FlashLight()
{
	DeleteLightHandle(lightHandle);
	AssetManager::ReleaseMesh(objHandle);
}

// @brief FlashLight�ǂݍ��ݏ��� //

void FlashLight::Load()
{
	lightAtten2 = 0.0005f;
	/*lightHandle = CreateSpotLightHandle(objPos, objDir,
		DX_PI_F / 6.0f, DX_PI_F / 4.0f, lightRange, 0.0f, 0.0f, lightAtten2);*/
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2 * 10);
}

// @brief FlashLight�X�V���� //

void FlashLight::Update(float deltaTime)
{
	ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
	SetLightPositionHandle(lightHandle, camera->GetPos());
	//SetLightDirectionHandle(lightHandle, camera->GetDir());
}

// @brief FlashLight�`�揈�� //

void FlashLight::Draw()
{
}