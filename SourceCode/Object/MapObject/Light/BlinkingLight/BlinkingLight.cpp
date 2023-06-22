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

BlinkingLight::BlinkingLight(VECTOR pos)
    :LightBase(pos)
{
    Load();
}

// デストラクタ //

BlinkingLight::~BlinkingLight()
{
    DeleteLightHandle(lightHandle);
    AssetManager::ReleaseMesh(objHandle);
}

// 読み込み処理 //

void BlinkingLight::Load()
{
    //ライト設定
    lightHandle = CreatePointLightHandle(objPos, lightRange, 0.0f, 0.0f, lightAtten2);

    //モデル設定
    MV1SetPosition(objHandle, objPos);
    MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
}

// 更新処理 //

void BlinkingLight::Update(float deltaTime)
{
    //カウントがインターバルを超えるたびに乱数を生成
    SetLightRangeAttenHandle(lightHandle, lightRange, 0.0f, 0.0f, lightAtten2);
    countTimer += deltaTime;
    if (countTimer >= intervalTime)
    {
        countTimer = 0;
        srand((unsigned int)time(NULL));
        intervalTime = static_cast <float>(rand() % 4 + 1);
    }

    //インターバルが1秒以下だったら点滅させる
    if (intervalTime <= 1)
    {
        isBlinking = !isBlinking;
    }
    else
    {
        //基本は点滅させない
        isBlinking = false;
    }

    //点滅時はライトの明るさ変更
    if (isBlinking)
    {
        lightAtten2 = 0.003f;
    }
    else
    {
        lightAtten2 = 0.002f;
    }

}

// 描画処理 //

void BlinkingLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}