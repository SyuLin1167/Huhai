#include "LitLight.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">:�V�[����</param>
/// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , lightDistance(0.0f)
{
    //���C�g�ݒ�
    SetLightEnableHandle(lightHandle,false);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
LitLight::~LitLight()
{
    //�����Ȃ�
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">:�t���[�����[�g</param>
void LitLight::Update(float deltaTime)
{
    //��苗���߂Â����甭��
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < ACTION_RANGE)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
        }
    }


    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

/// <summary>
/// �`�揈��
/// </summary>
void LitLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}