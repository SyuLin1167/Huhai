#pragma once
#include"../SceneBase/SceneBase.h"

/* PlayScene�N���X */
class Play :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Play();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Play();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���̃t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;
};