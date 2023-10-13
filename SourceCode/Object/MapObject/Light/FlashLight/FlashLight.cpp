#include "FlashLight.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
FlashLight::FlashLight()
    :LightBase()
{
    //���C�g�ݒ�
    DeleteLightHandle(lightHandle);
    lightHandle = CreateSpotLightHandle(objPos, objDir,
        DX_PI_F / 4.0f, DX_PI_F / 8.0f, LIGHT_RANGE, 0.0f, 0.0f, 0.0f);

    isVisible = false;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
FlashLight::~FlashLight()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�f���^�^�C��</param>
void FlashLight::Update(const float deltaTime)
{
    //�J�����̕����Ƀ��C�g�𓖂Ă�
    ObjBase* camera = ObjManager::GetFirstObj(ObjTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    SetLightDirectionHandle(lightHandle, camera->GetDir());


    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

/// <summary>
/// �`�揈��
/// </summary>
void FlashLight::Draw()
{
    //�����Ȃ�
}