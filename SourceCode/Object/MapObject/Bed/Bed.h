#pragma once

#include"../../ObjectBase/ObjectBase.h"

/*Bed�N���X*/
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
    /// �ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;
};
