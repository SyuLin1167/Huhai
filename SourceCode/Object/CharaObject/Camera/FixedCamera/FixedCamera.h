#pragma once
#include"../../../ObjectBase/ObjBase.h"

/// <summary>
/// FixedCamera�N���X
/// </summary>
class FixedCamera :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FixedCamera();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FixedCamera();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override ;

private:
    const VECTOR FIRST_POS = VGet(70, 6, 75);           //�������W
    const VECTOR FIRST_AIM_POS = VGet(-10, 10, 25);     //�����ڕW���W
};

