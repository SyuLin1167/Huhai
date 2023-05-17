#include "FlashLight.h"

// @brief FlashLight�R���X�g���N�^ //

FlashLight::FlashLight()
	:LightBase()
	,intervalTime(0.0f)
	,countTimer(0.0f)
	,lightFlash(false)
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
	MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// @brief FlashLight�X�V���� //

void FlashLight::Update(float deltaTime)
{

	DeleteLightHandle(lightHandle);
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetPosition(objHandle, objPos);
	if (countTimer >= intervalTime / 100)
	{
		countTimer = 0;
		srand((unsigned int)time(NULL));
		intervalTime = static_cast <float>(rand() % 4 + 1);
		if (intervalTime <= 1)
		{
			lightFlash = !lightFlash;
		}
		else
		{
			lightFlash = false;
		}
	}
	
	if (lightFlash)
	{
		lightAtten2 = 0.003f;
	}
	else
	{
		lightAtten2 = 0.002f;
	}

	countTimer += deltaTime;
}

// @brief FlashLight�`�揈�� //

void FlashLight::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
}