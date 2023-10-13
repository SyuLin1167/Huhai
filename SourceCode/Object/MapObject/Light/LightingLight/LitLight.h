#pragma once

#include"../LightBase/LightBase.h"

/// <summary>
/// LitLight�N���X
/// </summary>
class LitLight :public LightBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="scene">:�V�[����</param>
    /// <param name="num">:�I�u�W�F�N�g�ԍ�</param>
    LitLight(std::string scene, std::string num = "0");

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~LitLight();

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
    const COLOR_F LIT_MAT_COLOR;                //�������̃��C�g�̃}�e���A���J���[

    float lightDistance;                        //���C�g����̋���
    const float ACTION_RANGE = 55.0f;           //�����͈�
};
