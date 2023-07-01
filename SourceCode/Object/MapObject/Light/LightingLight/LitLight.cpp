#include "LitLight.h"

// �R���X�g���N�^ //

LitLight::LitLight(VECTOR pos, float range)
    :LightBase(pos)
    , lightDistance(0.0f)
    , actionRange(range)
{
    Load();
}

// �f�X�g���N�^ //

LitLight::~LitLight()
{
    //���C�g�폜
    DeleteLightHandle(lightHandle);

    //���f���폜
    AssetManager::ReleaseMesh(objHandle);
}

// �ǂݍ��ݏ��� //

void LitLight::Load()
{

    SetLightEnableHandle(lightHandle,FALSE);
}

        // �X�V���� //

void LitLight::Update(float deltaTime)
{
    //��苗���߂Â����甭��
    ObjBase* player = ObjManager::GetFirstObj(ObjectTag::Player);
    if (player)
    {
        lightDistance = VSize(player->GetPos() - objPos);

        if (abs(lightDistance) < actionRange)
        {
            SetLightEnableHandle(lightHandle, TRUE);
            lightMatColor = { 1.0f,1.0f,1.0f,1.0f };
            MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
        }
    }
}

// �`�揈�� //

void LitLight::Draw()
{
    //���f���`��
    MV1DrawModel(objHandle);
}