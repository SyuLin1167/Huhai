#include "TimeManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
TimeManager::TimeManager()
    : deltaTime(0)
{
    nowTime = (float)GetNowCount();
    prevTime = nowTime;
}

/// <summary>
/// デストラクタ
/// </summary>
TimeManager::~TimeManager()
{
    //処理なし
}

/// <summary>
/// DeltaTime取得処理
/// </summary>
/// <returns></returns>
const float TimeManager::DeltaTime()
{
    //フレームレート算出
    nowTime = static_cast<float>(GetNowCount());
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;

    return deltaTime;
}