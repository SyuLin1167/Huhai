#pragma once
#include <DxLib.h>

/*TimeManager�N���X*/
class TimeManager
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TimeManager();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~TimeManager();

    /// <summary>
    /// DeltaTime�擾����
    /// </summary>
    /// <returns>deltaTime</returns>
    const float DeltaTime();

private:
    float nowTime;      //���݂̎���
    float prevTime;     //�ߋ��̎���
    float deltaTime;    //�t���[�����[�g
};

