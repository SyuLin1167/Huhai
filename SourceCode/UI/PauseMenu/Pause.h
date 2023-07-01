#pragma once

#include"../../Scene/SceneBase/SceneBase.h"

class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    static PauseMenu* Init();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime) override;

    /// <summary>
    /// �}�E�X���͏���
    /// </summary>
    void MouseInput();

    /// <summary>
    /// �J�����̏㉺�^��
    /// </summary>
    /// <returns>����:true|���Ȃ�:false</returns>
    static bool IsMovementCamera() { if (pause) { return  pause->isSelect; }}

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;


private:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PauseMenu();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~PauseMenu();

    static PauseMenu* pause;		//���g�̎���

    int mouseX;
    int mouseY;
    bool canSelect;
    bool isSelect;                   //�I�����
    bool hasInput;                   //���̓t���O
};

