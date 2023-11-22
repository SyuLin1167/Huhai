#include "LitLight.h"

LitLight::LitLight(std::string scene, std::string num)
    :LightBase(scene, num)
    , LIT_MAT_COLOR{ 0.2f,0.2f,0.2f,1.0f }
    , lightDistance(0.0f)
{
    //���C�g�ݒ�
    SetLightEnableHandle(lightHandle,false);

    //���f���ݒ�
    MV1SetMaterialEmiColor(objHandle, 0, LIT_MAT_COLOR);
}

LitLight::~LitLight()
{
    //�����Ȃ�
}

void LitLight::Update(const float deltaTime)
{
    //��苗���߂Â����甭��
    ObjBase* player = ObjManager::GetFirstObj(ObjTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < ACTION_RANGE)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
        }
    }


    //�p�����[�^�[�ɂ�鋗������
    AttenByParam();
}

void LitLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}