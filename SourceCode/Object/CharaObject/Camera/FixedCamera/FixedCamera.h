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
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(const float deltaTime) override;

    /// <summary>
    /// �`��
    /// </summary>
    void Draw() override ;
};

