#pragma once
#include<unordered_map>
#include<string>

#include"../../Scene/SceneBase/SceneBase.h"

/*PauseMenu�N���X*/
class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// ����������
    /// </summary>
    /// <param name="screen">:�Q�[�����</param>
    static SceneBase* Init();

    /// <summary>
    /// �㏈��
    /// </summary>
    static void Finalize();

    /// <summary>
    /// �{�^���ǉ�����
    /// </summary>
    /// <param name="name">:�o�^��</param>
    void AddButton(std::string name);


    /// <summary>
    /// �p�����[�^�[�ǉ�����
    /// </summary>
    /// <param name="name">:�o�^��</param>
    /// <param name="value">:�p�����[�^�[�����l</param>
    void AddParam(std::string name,int value);

    /// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="deltaTime">:�t���[�����[�g</param>
    /// <returns>���t���[���̃V�[��</returns>
    SceneBase* Update(float deltaTime) override;

    /// <summary>
    /// �X�e�[�^�X���
    /// </summary>
    /// <param name="name">:�{�^����</param>
    /// <returns>�I��:true|�I�t:false</returns>
    static bool HasStatus(std::string name);

    /// <summary>
    /// �^�C�g���ړ�
    /// </summary>
    /// <returns>�ړ�����:true|���Ȃ�:false</returns>
    static bool BackToTitle();

    /// <summary>
    /// �p�����[�^�[�擾
    /// </summary>
    /// <param name="name">:�p�����[�^�[��</param>
    /// <returns>:�p�����[�^�[</returns>
    static int Parameter(std::string name);

    /// <summary>
    /// �^�C�g���{�^�����Z�b�g
    /// </summary>
    static void ResetTitleButton();

    /// <summary>
    /// �`�揈��
    /// </summary>
    void Draw()override;

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    PauseMenu();

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~PauseMenu();

    static PauseMenu* pause;        //���g�̎���

    std::unordered_map<std::string, class Button*> buttonData;      //�{�^���f�[�^
    std::unordered_map<std::string, class ParamButton*> paramData;      //�p�����[�^�[�f�[�^

    class TitleButton* titleButton;         //�^�C�g���{�^��
};

