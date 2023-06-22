#pragma once

#include"../LightBase/LightBase.h"

/*NomalLight�N���X*/
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    NomalLight();

    /// <summary>
    /// �R���g���N�^
    /// </summary>
    /// <param name="pos">:���[���h���W</param>
    NomalLight(VECTOR pos);


    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~NomalLight();

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
