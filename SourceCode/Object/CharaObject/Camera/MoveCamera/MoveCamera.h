#pragma once
#include"../../../ObjectBase/ObjectBase.h"

/*MoveCamera�N���X*/
class MoveCamera :public ObjBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MoveCamera();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~MoveCamera() {};

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override {};

    /// <summary>
    /// �`��
    /// </summary>
    void Draw()override {};

};

