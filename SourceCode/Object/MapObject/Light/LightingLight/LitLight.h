#pragma once

#include"../LightBase/LightBase.h"

        /*LitLight�N���X*/
class LitLight :public LightBase
{
public:
    /// <summary>
    /// LitLight�R���X�g���N�^
    /// </summary>
    LitLight();

    /// <summary>
    /// LitLight�R���X�g���N�^
    /// </summary>
    /// <param name="lightPos">:���C�g�̃��[���h���W</param>
    /// <param name="litRange">:�_���͈�</param>
    LitLight(VECTOR lightPos, float range);

    /// <summary>
    /// LitLight�f�X�g���N�^
    /// </summary>
    ~LitLight();

    /// <summary>
    /// LitLight�ǂݍ��ݏ���
    /// </summary>
    void Load();

    /// <summary>
    /// LitLight�X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    void Update(float deltaTime)override;

    /// <summary>
    /// LitLight�`�揈��
    /// </summary>
    void Draw()override;

private:
    float lightDistance;        //���C�g����̋���
    float actionRange;        //�����͈�
};
