#include "TimeManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
TimeManager::TimeManager()
    : deltaTime(0)
{
    nowTime = (float)GetNowCount();
    prevTime = nowTime;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
TimeManager::~TimeManager()
{
    //�����Ȃ�
}

/// <summary>
/// DeltaTime�擾����
/// </summary>
/// <returns></returns>
const float TimeManager::DeltaTime()
{
    //�t���[�����[�g�Z�o
    nowTime = static_cast<float>(GetNowCount());
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;

    return deltaTime;
}