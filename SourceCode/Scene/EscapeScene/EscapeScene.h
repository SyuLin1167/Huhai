#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// �E�o�̃V�[��
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
    /// <param name="deltaTime">:�f���^�^�C��</param>
    /// <returns>���̃t���[���̃V�[��</returns>
    SceneBase* UpdateScene(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene() override;
};

