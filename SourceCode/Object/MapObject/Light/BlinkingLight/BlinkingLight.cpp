#include "BlinkingLight.h"
#include"../../../../Shade/Bloom/Bloom.h"

// コンストラクタ //

BlinkingLight::BlinkingLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
}


// デストラクタ //

BlinkingLight::~BlinkingLight()
{
}
// 更新処理 //

void BlinkingLight::Update(float deltaTime)
{
    //カウントがインターバルを超えるたびに乱数を生成
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
        SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2 + BLINK_PARAM);
        MV1SetMaterialEmiColor(objHandle, 0, BLINK_COLOR);
    }
    else
    {
        SetLightRangeAttenHandle(lightHandle, LIGHT_RANGE, 0.0f, 0.0f, lightAtten2);
        MV1SetMaterialEmiColor(objHandle, 0, lightMatColor);
    }

    //パラメーターによる距離減衰
    AttenByParam();
}

// 描画処理 //

void BlinkingLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}