#pragma once

#include"../SceneBase/SceneBase.h"

/* PlayScene�N���X */
class PlayScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayScene();

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