#include "BlinkingLight.h"

        // コンストラクタ //

BlinkingLight::BlinkingLight()
    :LightBase()
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
    Load();
}

        // コンストラクタ //

BlinkingLight::BlinkingLight(VECTOR lightPos)
    :LightBase(lightPos)
{
    Load();
}

        // デストラクタ //

BlinkingLight::~BlinkingLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

        // @brief BlinkingLight読み込み処理 //

void BlinkingLight::Load()
{
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);
    MV1SetPosition(objHandle, objPos);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

        // 更新処理 //

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

        // 描画処理 //

void BlinkingLight::Draw()
{
    MV1DrawModel(objHandle);						//モデル描画
}