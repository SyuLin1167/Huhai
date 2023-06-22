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

// 更新処理 //

void TimeManager::Update()
{
    //フレームレート算出
    nowTime = (float)GetNowCount();
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;
}