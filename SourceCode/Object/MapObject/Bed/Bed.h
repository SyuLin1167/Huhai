#pragma once

#include"../../ObjectBase/ObjBase.h"

/// <summary>
/// �x�b�h�I�u�W�F�N�g
/// </summary>
class Bed :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Bed();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Bed();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw() override;

private:
    VECTOR sleepPos;                                //���������W
    const VECTOR SLEEP_AIM_POS=VGet(0, 8, 0);       //�������ڐ����W
};
