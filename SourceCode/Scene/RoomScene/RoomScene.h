#pragma once

#include"../SceneBase/SceneBase.h"

/// <summary>
/// RoomScene�N���X
/// </summary>
class RoomScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    RoomScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~RoomScene();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�f���^�^�C��</param>
    /// <returns>���t���[���̃V�[��</returns>
    SceneBase* UpdateScene(const float deltaTime) override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene() override;
};
