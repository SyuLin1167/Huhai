#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// PlayScene�N���X
/// </summary>
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
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene()override;
};