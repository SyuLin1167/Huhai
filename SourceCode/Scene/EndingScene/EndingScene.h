#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// EndingScene�N���X
/// </summary>
class EndingScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EndingScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EndingScene();

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
