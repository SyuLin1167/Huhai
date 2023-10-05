#pragma once

#include"../LightBase/LightBase.h"

/*LitLight�N���X*/
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
    float lightDistance;        //���C�g����̋���
    const float ACTION_RANGE = 55.0f;          //�����͈�
};
