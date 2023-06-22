#include "NomalLight.h"

// �R���X�g���N�^ //

NomalLight::NomalLight()
    :LightBase()
{
    Load();
}

// �R���X�g���N�^ //

NomalLight::NomalLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// �f�X�g���N�^ //

NomalLight::~NomalLight()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);

    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
}

// �ǂݍ��ݏ��� //

void NomalLight::Load()
{
    //���C�g�ݒ�
    SetLightPositionHandle(lightHandle, objPos);

    //���f���ݒ�
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    MV1SetPosition(objHandle, objPos);
}

// �X�V���� //

void NomalLight::Update(float deltaTime)
{
    //���W�X�V
    SetLightPositionHandle(lightHandle, objPos);
    MV1SetPosition(objHandle, objPos);
}

// �`�揈�� //

void NomalLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}