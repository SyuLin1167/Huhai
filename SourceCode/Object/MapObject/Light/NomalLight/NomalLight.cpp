#include "NomalLight.h"

        // �R���X�g���N�^ //

NomalLight::NomalLight()
    :LightBase()
{
    Load();
}

        // �R���X�g���N�^ //

NomalLight::NomalLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // �f�X�g���N�^ //

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
    SetLightPositionHandle(lightHandle, objPos);
    MV1SetPosition(objHandle, objPos);
}

        // @brief NomalLight�`�揈�� //

void NomalLight::Draw()
{
    MV1DrawModel(objHandle);						//���f���`��
}