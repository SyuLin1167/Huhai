#include "FlashLight.h"

        // �R���X�g���N�^ //

FlashLight::FlashLight()
    :LightBase()
{
    Load();
}

        // �R���X�g���N�^ //

FlashLight::FlashLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // �f�X�g���N�^ //

FlashLight::~FlashLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

        // �ǂݍ��ݏ��� //

void FlashLight::Load()
{
    lightAtten2 = 0.0005f;
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2 * 10);
}

        // �X�V���� //

void FlashLight::Update(float deltaTime)
{
    ObjectBase* camera = ObjManager::GetFirstObj(ObjectTag::Camera);
    SetLightPositionHandle(lightHandle, camera->GetPos());
    //SetLightDirectionHandle(lightHandle, camera->GetDir());
}

        // �`�揈�� //

void FlashLight::Draw()
{
}