#pragma once
#include"../../../ObjectBase/ObjBase.h"

/*FixedCamera�N���X*/
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
    ~FixedCamera() {};

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override {};

    /// <summary>
    /// �`��
    /// </summary>
    void Draw()override ;
};

