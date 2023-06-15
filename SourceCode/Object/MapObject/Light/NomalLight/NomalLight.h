#pragma once

#include"../LightBase/LightBase.h"

        /*NomalLight�N���X*/
class NomalLight :public LightBase
{
public:
    /// <summary>
    /// NomalLight�R���X�g���N�^
    /// </summary>
    NomalLight();

    /// <summary>
    /// NomalLight�R���g���N�^
    /// </summary>
    /// <param name="lightPos">:���C�g�̃��[���h���W</param>
    NomalLight(VECTOR lightPos);


    /// <summary>
    /// NomalLight�f�X�g���N�^
    /// </summary>
    ~NomalLight();

    /// <summary>
    /// NomalLight�ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// NomalLight�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;


    /// <summary>
    /// NomalLight�`�揈��
    /// </summary>
    void Draw()override;
};
