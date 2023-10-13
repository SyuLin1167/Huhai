#pragma once
#include"../SceneBase/SceneBase.h"

/// <summary>
/// PauseScene�N���X
/// </summary>
class PauseScene:public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PauseScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PauseScene();

    /// <summary>
    /// �|�[�Y���j���[����������
    /// </summary>
    void InitPauesMenu();

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

private:
    const int PIXEL_WIDTH = 8;                                          //�s�N�Z����
    const int GAUSS_PARAM = 1400;                                       //�ڂ����l
};

