#include "FlashLight.h"

// �R���X�g���N�^ //

FlashLight::FlashLight()
    :LightBase()
{
    Load();
}

// �R���X�g���N�^ //

FlashLight::FlashLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// �f�X�g���N�^ //

FlashLight::~FlashLight()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);
}

// �ǂݍ��ݏ��� //

void FlashLight::Load()
{
    //���C�g�ݒ�
    DeleteLightHandle(lightHandle);
    lightHandle = CreateSpotLightHandle(objPos, objDir, DX_PI_F / 4.0f, DX_PI_F / 8.0f, lightRange, 0.0f, 0.0f, 0.0f);

    isVisible = false;
}

// �X�V���� //

void FlashLight::Update(float deltaTime)
{
    //�v���C���[�̎��ӂ����点��
    ObjBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    SetLightDirectionHandle(lightHandle, camera->GetDir());


    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

// �`�揈�� //

void FlashLight::Draw()
{
}