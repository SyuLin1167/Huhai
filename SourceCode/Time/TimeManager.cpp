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

// �X�V���� //

void TimeManager::Update()
{
    //�t���[�����[�g�Z�o
    nowTime = (float)GetNowCount();
    deltaTime = (nowTime - prevTime) / 1000.0f;
    prevTime = nowTime;
}