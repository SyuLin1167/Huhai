#pragma once
#include"../../../ObjectBase/ObjectBase.h"

    /*MoveCamera�N���X*/
class MoveCamera :public ObjectBase
{
public:
    /// <summary>
    /// MoveCamera�R���X�g���N�^
    /// </summary>
    MoveCamera();

    /// <summary>
    /// MoveCamera�f�X�g���N�^
    /// </summary>
    ~MoveCamera() {};

    /// <summary>
    /// MoveCamera�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override {};

    /// <summary>
    /// MoveCamera�`��
    /// </summary>
    void Draw()override {};

};

