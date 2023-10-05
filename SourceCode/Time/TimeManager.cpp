#include "TimeManager.h"

// r�R���X�g���N�^ //

TimeManager::TimeManager()
    : deltaTime(0)
{
    nowTime = (float)GetNowCount();
    prevTime = nowTime;
}

// �f�X�g���N�^ //

TimeManager::~TimeManager()
{
}

// DeltaTime�擾���� //

const float TimeManager::DeltaTime()
{
    //�t���[�����[�g�Z�o
    nowTime = static_cast<float>(GetNowCount());
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;

    return deltaTime;
}