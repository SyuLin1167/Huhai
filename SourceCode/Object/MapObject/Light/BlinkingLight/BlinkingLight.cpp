#include "BlinkingLight.h"
#include"../../../../Shade/Bloom/Bloom.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">:シーン名</param>
/// <param name="num">:オブジェクト番号</param>
BlinkingLight::BlinkingLight(std::string scene, std::string num)
    :LightBase(scene,num)
    , intervalTime(0.0f)
    , countTimer(0.0f)
    , isBlinking(false)
{
    //処理なし
}


/// <summary>
/// デストラクタ
/// </summary>
BlinkingLight::~BlinkingLight()
{
    //処理なし
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime">:デルタタイム</param>
void BlinkingLight::Update(const float deltaTime)
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
            MV1SetMaterialEmiColor(objHandle, 0, LIGHT_MAT_COLOR);
        }

        //パラメーターによる距離減衰
        AttenByParam();
}

/// <summary>
/// 描画処理
/// </summary>
void BlinkingLight::Draw()
{
    //モデル描画
    MV1DrawModel(objHandle);
}