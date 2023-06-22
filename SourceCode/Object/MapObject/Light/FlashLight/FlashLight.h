#pragma once
#include"../LightBase/LightBase.h"

/*FlashLighit�N���X*/
class FlashLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FlashLight();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="lightPos">:���C�g�̃��[���h���W</param>
    FlashLight(VECTOR lightPos);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~FlashLight();

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
