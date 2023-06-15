#include "BlinkingLight.h"

        // �R���X�g���N�^ //

BlinkingLight::BlinkingLight()
    :LightBase()
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
    Load();
}

        // �R���X�g���N�^ //

BlinkingLight::BlinkingLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // �f�X�g���N�^ //

BlinkingLight::~BlinkingLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

        // @brief BlinkingLight�ǂݍ��ݏ��� //

void BlinkingLight::Load()
{
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    MV1SetPosition(objHandle, objPos);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

        // �X�V���� //

void BlinkingLight::Update(float deltaTime)
{

    SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);

    if (countTimer >= intervalTime)
    {
        countTimer = 0;
        srand((unsigned int)time(NULL));
        intervalTime = static_cast <float>(rand() % 4 + 1);
    }

    if (intervalTime <= 1)
    {
        isBlinking = !isBlinking;
    }
    else
    {
        isBlinking = false;
    }

    if (isBlinking)
    {
        lightAtten2 = 0.003f;
    }
    else
    {
        lightAtten2 = 0.002f;
    }

    countTimer += deltaTime;
}

        // �`�揈�� //

void BlinkingLight::Draw()
{
    MV1DrawModel(objHandle);						//���f���`��
}