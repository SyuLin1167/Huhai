#pragma once

#include"../SceneBase/SceneBase.h"

/*Ending�N���X*/
class Ending :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ending();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Ending();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <returns>���̃t���[���̃V�[��</returns>
    SceneBase* UpdateScene(const float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void DrawScene()override;
};
