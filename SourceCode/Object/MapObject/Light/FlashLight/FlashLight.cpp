#include "FlashLight.h"

// �R���X�g���N�^ //

FlashLight::FlashLight()
    :LightBase()
{
    //���C�g�ݒ�
    DeleteLightHandle(lightHandle);
    lightHandle = CreateSpotLightHandle(objPos, objDir,
        DX_PI_F / 4.0f, DX_PI_F / 8.0f, LIGHT_RANGE, 0.0f, 0.0f, 0.0f);

    isVisible = false;
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
    //�����Ȃ�
}

// �X�V���� //

void FlashLight::Update(float deltaTime)
{
    //�J�����̕����Ƀ��C�g�𓖂Ă�
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