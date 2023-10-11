#include "LitLight.h"

// �R���X�g���N�^ //

LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , lightDistance(0.0f)
{
    //���C�g�ݒ�
    SetLightEnableHandle(lightHandle,false);
}

// �f�X�g���N�^ //

LitLight::~LitLight()
{
    //�����Ȃ�
}

// �X�V���� //

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

// �`�揈�� //

void LitLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}