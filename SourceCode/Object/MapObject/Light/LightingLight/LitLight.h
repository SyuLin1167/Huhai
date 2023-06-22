#pragma once

#include"../LightBase/LightBase.h"

/*LitLight�N���X*/
class LitLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    LitLight();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">:���[���h���W</param>
    /// <param name="range">:�_���͈�</param>
    LitLight(VECTOR pos, float range);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~LitLight();

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

private:
    float lightDistance;        //���C�g����̋���
    float actionRange;          //�����͈�
};
