#pragma once
#include"../SceneBase/SceneBase.h"

/*ResultScene�N���X*/
class ResultScene :public SceneBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ResultScene();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~ResultScene();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime"></param>
    /// <returns>���̃t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime)override;

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;
};
