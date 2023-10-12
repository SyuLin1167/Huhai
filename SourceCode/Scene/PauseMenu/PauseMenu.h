#pragma once
#include<unordered_map>
#include<string>

#include"../../Scene/SceneBase/SceneBase.h"

/// <summary>
/// PauseMenu�N���X
/// </summary>
class PauseMenu:public SceneBase
{
public:
    /// <summary>
    /// �C���X�^���X��������
    /// </summary>
    static void CreateInstance();

    /// <summary>
    /// �|�[�Y���j���[�̃C���X�^���X�擾����
    /// </summary>
    /// <returns>�|�[�Y���j���[</returns>
    static SceneBase* GetPauseMenuInstance();

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
    SceneBase* UpdateScene(float deltaTime) override;

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
    void DrawScene()override;

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PauseMenu();

private:
    /// <summary>
    /// �R���X�g���N�^(�V���O���g��)
    /// </summary>
    PauseMenu();

    static std::unique_ptr<PauseMenu> pauseMenu;                        //���g�̎���

    const int PIXEL_WIDTH = 8;                                          //�s�N�Z����
    const int GAUSS_PARAM = 1400;                                       //�ڂ����l

    std::unordered_map<std::string, class Button*> buttonData;          //�{�^���f�[�^
    std::unordered_map<std::string, class ParamButton*> paramData;      //�p�����[�^�[�f�[�^

    class TitleButton* titleButton;                                     //�^�C�g���{�^��
};

