#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// EscapeScene�N���X
/// </summary>
class EscapeScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EscapeScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EscapeScene();

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

