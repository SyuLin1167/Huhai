#pragma once

#include"../SceneBase/SceneBase.h"

/*EscapeScene�N���X*/
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

