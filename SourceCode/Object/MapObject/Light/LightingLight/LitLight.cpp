#include "LitLight.h"

// @brief LitLight�R���X�g���N�^ //

LitLight::LitLight()
    :LightBase()
    ,lightDistance(0.0f)
{
    Load();
}

// @brief LitLight�R���X�g���N�^ //

LitLight::LitLight(VECTOR lightPos, float range)
    :LightBase(lightPos)
    , lightDistance(0.0f)
    , actionRange(range)
{
    Load();
}

// @brief LitLight�f�X�g���N�^ //

LitLight::~LitLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

// @brief LitLight�ǂݍ��ݏ��� //

void LitLight::Load()
{    
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    SetLightEnableHandle(lightHandle, FALSE);
}

// @brief LitLight�X�V���� //

void LitLight::Update(float deltaTime)
{
    //---�I�u�W�F�N�g�̒��g����---//
    ObjectBase* player = ObjManager::GetFirstObj(ObjectTag::Player);        //�v���C���[�I�u�W�F�N�g�擾
    if (player)
    {
        //---���C�g�̓_������---//
        lightDistance = VSize(player->GetPos() - objPos);                       //�v���C���[�ƃ��C�g�Ƃ̋����擾

        if (abs(lightDistance) < actionRange)                                         //��苗���߂Â�����
        {
            SetLightEnableHandle(lightHandle, TRUE);
            lightMatColor = { 1.0f,1.0f,1.0f,1.0f };                            //�P�x�𖾂邭�����F�𔒂ɂ���
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);                    //�P�x�Ɣ����F�ݒ�
        }
    }
}

// @brief LitLight�`�揈�� //

void LitLight::Draw()
{
    MV1DrawModel(objHandle);                                                //���f���`��
}