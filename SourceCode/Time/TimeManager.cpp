#include "TimeManager.h"

// rコンストラクタ //

TimeManager::TimeManager()
    : deltaTime(0)
{
    nowTime = (float)GetNowCount();
    prevTime = nowTime;
}

// デストラクタ //

TimeManager::~TimeManager()
{
}

// DeltaTime取得処理 //

const float TimeManager::DeltaTime()
{
    //フレームレート算出
    nowTime = static_cast<float>(GetNowCount());
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;

    return deltaTime;
}