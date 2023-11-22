#include "TimeManager.h"

TimeManager::TimeManager()
    : deltaTime(0)
{
    nowTime = (float)GetNowCount();
    prevTime = nowTime;
}

TimeManager::~TimeManager()
{
    //�����Ȃ�
}

const float TimeManager::DeltaTime()
{
    //�t���[�����[�g�Z�o
    nowTime = static_cast<float>(GetNowCount());
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;

    return deltaTime;
}