#include "NomalLight.h"

// @brief NomalLight�R���X�g���N�^ //

NomalLight::NomalLight()
	:LightBase()
{
	Load();
}

// @brief NomalLight�R���X�g���N�^ //

NomalLight::NomalLight(VECTOR lightPos)
	:LightBase(lightPos)
{
	Load();
}

// @brief NomalLight�f�X�g���N�^ //

NomalLight::~NomalLight()
{
	DeleteLightHandle(lightHandle);
	AssetManager::ReleaseMesh(objHandle);
}

// @brief NomalLight�ǂݍ��ݏ��� //

void NomalLight::Load()
{
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// @brief NomalLight�X�V���� //

void NomalLight::Update(float deltaTime)
{
	DeleteLightHandle(lightHandle);
	lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
	MV1SetPosition(objHandle, objPos);
}


// @brief NomalLight�`�揈�� //

void NomalLight::Draw()
{
	MV1DrawModel(objHandle);						//���f���`��
}